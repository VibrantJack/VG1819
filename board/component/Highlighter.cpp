#include "Highlighter.h"
#include "kitten/QuadRenderable.h"
#include "board/tile/TileInfo.h"
#include "board/BoardManager.h"
#include <iostream>
Highlighter::Highlighter()
{
	for (int i = TileInfo::ForArea; i != TileInfo::Last; i++)
	{
		m_listForType[static_cast<TileInfo::HighlightType>(i)] = std::vector<kitten::K_GameObject*>();
	}

	m_texMap[TileInfo::ForArea] = "";
	m_texMap[TileInfo::ForRange] = "";
	m_texMap[TileInfo::ForOwnedTile] = "";
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

	//if there are tiles needs to change its highlight type
	if (!m_toBeChanged.empty())
	{
		for (int i = 0; i < m_toBeChanged.size(); i++)
		{
			kitten::K_GameObject* tile = m_toBeChanged[i];
			TileInfo * info = tile->getComponent<TileInfo>();

			TileInfo::HighlightType type = info->getHighlightType();

			int x = info->getPosX();
			int z = info->getPosY();

			if (type != TileInfo::Last)
			{
				//add blend
				
			}
			else
			{
				//remove blend
			}
		}

		m_toBeChanged.clear();//changes done, remove from list
	}

	/*
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
	}*/
}

void Highlighter::highlightTile(TileInfo::HighlightType p_type, kitten::Event::TileList p_list)
{
	for (int i = 0; i < p_list.size(); i++)
	{
		kitten::K_GameObject* tile = BoardManager::getInstance()->getTile(p_list[i].first, p_list[i].second);
		TileInfo* tileInfo = tile->getComponent<TileInfo>();

		//set it's highlight
		tileInfo->setHighlighted(p_type, true);

		//add it to change list
		m_toBeChanged.push_back(tile);

		//add it to corresponding type list
		m_listForType[p_type].push_back(tile);
	}
}

void Highlighter::unhighlightTile(TileInfo::HighlightType p_type, kitten::Event::TileList p_list)
{
	for (int i = 0; i < p_list.size(); i++)
	{
		kitten::K_GameObject* tile = BoardManager::getInstance()->getTile(p_list[i].first, p_list[i].second);
		TileInfo* tileInfo = tile->getComponent<TileInfo>();

		//set it's highlight
		tileInfo->setHighlighted(p_type, false);

		//add it to change list
		m_toBeChanged.push_back(tile);

		//remove it from corresponding type list
		for (int j = 0; j < m_listForType[p_type].size(); j++)
		{
			if (m_listForType[p_type].at(j) == tile)
			{
				m_listForType[p_type].erase(m_listForType[p_type].begin() + j);
			}
		}
	}
}

void Highlighter::unhighlightAll(TileInfo::HighlightType p_type)
{
	std::vector<kitten::K_GameObject*> list = m_listForType[p_type];

	for (int i = 0; i < list.size(); i++)
	{
		TileInfo* tileInfo = list[i]->getComponent<TileInfo>();

		//set it's highlight
		tileInfo->setHighlighted(p_type, false);

		//add it to change list
		m_toBeChanged.push_back(list[i]);
	}

	//remove the list
	m_listForType[p_type].clear();
}

/*
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
}*/


