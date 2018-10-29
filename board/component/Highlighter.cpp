#include "Highlighter.h"
#include "kitten/QuadRenderable.h"
#include "board/tile/TileInfo.h"
#include "board/BoardManager.h"

Highlighter::Highlighter()
{
}

Highlighter::~Highlighter()
{
}

bool Highlighter::hasUpdate() const
{
	return true;
}

void Highlighter::start()
{
}

void Highlighter::update()
{
	kitten::K_GameObject* tile;

	// If there are tiles to be highlighted and there are already highlighted tiles
	//	then unhighlight already highlighted tiles to prepare for new highlights
	if (!m_toBeHighlighted.empty() && !m_lastHighlighted.empty())
	{
		printf("ToBeHighlighted full and lastHighlighted full\n");
		m_toBeUnhighlighted = m_lastHighlighted;
		m_lastHighlighted.clear();
	}

	// Remove color tint from tiles to be unhighlighted
	unhighlightTile();

	if (!m_toBeHighlighted.empty())
	{
		auto it = m_toBeHighlighted.cbegin();
		for (; it != m_toBeHighlighted.cend(); ++it)
		{
			tile = BoardManager::getInstance()->getTile(it->first, it->second);

			kitten::QuadRenderable* quad = tile->getComponent<kitten::QuadRenderable>();
			quad->setTexture("textures/tiles/highlightedGrassland.tga");

			TileInfo* tileInfo = tile->getComponent<TileInfo>();
			tileInfo->setHighlighted(true);
			tileInfo->setHighlightedBy(m_sHighlightedBy);
		}

		m_lastHighlighted = m_toBeHighlighted;
		m_toBeHighlighted.clear();
	}
}

void Highlighter::highlightTile(kitten::Event::TileList p_list)
{
	m_toBeHighlighted = p_list;
}

void Highlighter::unhighlightTile()
{
	kitten::K_GameObject* tile;
	TileInfo* tileInfo;
	auto it = m_toBeUnhighlighted.cbegin();
	for (; it != m_toBeUnhighlighted.cend(); ++it)
	{
		tile = BoardManager::getInstance()->getTile(it->first, it->second);
		tileInfo = tile->getComponent<TileInfo>();

		if (tileInfo->getOwnerId() == "NONE") {

			kitten::QuadRenderable* quad = tile->getComponent<kitten::QuadRenderable>();
			quad->setTexture("textures/tiles/grassland.tga");

			tileInfo->setHighlighted(false);
			tileInfo->setHighlightedBy("NONE");
		}
		else
		{
			kitten::QuadRenderable* quad = tile->getComponent<kitten::QuadRenderable>();
			quad->setColorTint(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));

			tileInfo->setHighlighted(false);
			tileInfo->setHighlightedBy("NONE");
		}
	}

	m_toBeUnhighlighted.clear();
}

void Highlighter::unHighlightCurrent()
{
	if (!m_lastHighlighted.empty())
	{
		m_toBeUnhighlighted = m_lastHighlighted;
		m_lastHighlighted.clear();
	}
}

