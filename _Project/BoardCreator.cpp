// BoardCreator
//
// Originally only created the tile objects that make up the board @Callum
// Multipurposed to handle highlighting and unhighlighting of tiles @Ken
// *Should rename component to something that better represents this.
// TODO: Either verify tiles to be highlighted are valid here or ensure it is
//	done before the tile list is sent here. E.g. A commander cannot highlight
//	tiles owned by the other commander

#include "BoardCreator.h"
#include "PrintWhenClicked.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"

#include "TileInfo.h"
#include "kitten\QuadRenderable.h"
#include "UseAbilityWhenClicked.h"
#include "_Project\ManipulateTileOnClick.h"

kitten::K_GameObject* BoardCreator::m_pTileList[15][15];

BoardCreator::BoardCreator()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Highlight_Tile,
		this,
		std::bind(&BoardCreator::highlightTile, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Unhighlight_Tile,
		this,
		std::bind(&BoardCreator::unhighlightCurrent, this, std::placeholders::_1, std::placeholders::_2));
}

BoardCreator::~BoardCreator()
{

}

bool BoardCreator::hasUpdate() const
{
	return true;
}

void BoardCreator::start()
{
	kitten::K_GameObjectManager* gameObjMan = kitten::K_GameObjectManager::getInstance();
	kitten::K_ComponentManager* compMan = kitten::K_ComponentManager::getInstance();

	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			kitten::K_GameObject* testTile = gameObjMan->createNewGameObject("tileobj.txt");
			m_pTileList[x][z] = testTile;

			PrintWhenClicked* printWhenClick = static_cast<PrintWhenClicked*>(compMan->createComponent("PrintWhenClicked"));
			printWhenClick->setMessage("grassy tile: " + std::to_string(x) + ", " + std::to_string(z));
			testTile->addComponent(printWhenClick);

			ManipulateTileOnClick* manipTileOnClick = static_cast<ManipulateTileOnClick*>(compMan->createComponent("ManipulateTileOnClick"));
			testTile->addComponent(manipTileOnClick);		

			// Error when Tile QuadRenderable component is not static and is destroyed on click
			//K_Component* destroyWhenClick = compMan->createComponent("DestroyOnClick");
			//testTile->addComponent(destroyWhenClick);

			K_Component* tileInfo = new TileInfo(x, z);
			testTile->addComponent(tileInfo);

			K_Component* clickBox = compMan->createComponent("ClickableBox");
			testTile->addComponent(clickBox);

			//K_Component* destroyWhenClick = compMan->createComponent("DestroyOnClick");
			//testTile->addComponent(destroyWhenClick);


			kitten::Transform& transform = testTile->getTransform();
			transform.setParent(&m_attachedObject->getTransform());
			transform.setIgnoreParent(false);
			transform.move(x, -1, z);
		}
	}

	kitten::K_Component* powerTracker = compMan->createComponent("PowerTracker");
	m_attachedObject->addComponent(powerTracker);

	//compMan->destroyComponent(this);
}

void BoardCreator::update()
{
	kitten::K_GameObject* tile;

	// If there are tiles to be highlighted and there are already highlighted tiles
	//	then unhighlight already highlighted tiles to prepare for new highlights
	if (!m_toBeHighlighted.empty() && !m_lastHighlighted.empty())
	{
		m_toBeUnhighlighted = m_lastHighlighted;
		m_lastHighlighted.clear();
	}

	// Remove color tint from tiles to be unhighlighted
	unhighlightTiles(kitten::Event::EventType::Unhighlight_Tile, nullptr);

	if (!m_toBeHighlighted.empty())
	{
		auto it = m_toBeHighlighted.cbegin();
		for (; it != m_toBeHighlighted.cend(); ++it)
		{
			tile = m_pTileList[it->first][it->second];

			kitten::QuadRenderable* quad = tile->getComponent<kitten::QuadRenderable>();
			quad->setColorTint(glm::vec4(0.0f, 0.0f, 0.5f, 1.0f));

			TileInfo* tileInfo = tile->getComponent<TileInfo>();
			tileInfo->setHighlighted(true);
			tileInfo->setHighlightedBy(m_sHighlightedBy);
		}

		m_lastHighlighted = m_toBeHighlighted;
		m_toBeHighlighted.clear();
	}
}

void BoardCreator::highlightTile(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_toBeHighlighted = *p_data->getTileList();
	m_sHighlightedBy = p_data->getString(TILE_OWNER_KEY);
}

void BoardCreator::unhighlightTiles(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	kitten::K_GameObject* tile;
	TileInfo* tileInfo;
	auto it = m_toBeUnhighlighted.cbegin();
	for (; it != m_toBeUnhighlighted.cend(); ++it)
	{
		tile = m_pTileList[it->first][it->second];
		tileInfo = tile->getComponent<TileInfo>();

		if (tileInfo->getOwnerId() == "NONE") {
			
			kitten::QuadRenderable* quad = tile->getComponent<kitten::QuadRenderable>();
			quad->setColorTint(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

			tileInfo->setHighlighted(false);
			tileInfo->setHighlightedBy("NONE");
		}
	}

	m_toBeUnhighlighted.clear();
}

void BoardCreator::unhighlightCurrent(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_toBeUnhighlighted = m_lastHighlighted;
	m_lastHighlighted.clear();
}