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
#include "_Project\SendSelfOnClick.h"

kitten::K_GameObject* BoardCreator::m_pTileList[15][15];

BoardCreator::BoardCreator()
{
	// Adding listeners for events
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Highlight_Tile,
		this,
		std::bind(&BoardCreator::highlightTile, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Unhighlight_Tile,
		this,
		std::bind(&BoardCreator::unhighlightCurrent, this, std::placeholders::_1, std::placeholders::_2));
	// End adding listeners for events

	// Initializing Tiles on board
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

			SendSelfOnClick* sendSelfOnClick = static_cast<SendSelfOnClick*>(compMan->createComponent("SendSelfOnClick"));
			testTile->addComponent(sendSelfOnClick);

			K_Component* tileInfo = new TileInfo(x, z);
			testTile->addComponent(tileInfo);

			K_Component* clickBox = compMan->createComponent("ClickableBox");
			testTile->addComponent(clickBox);

			kitten::Transform& transform = testTile->getTransform();
			transform.move(x, -1, z);
		}
	}
	// End initializing tiles on board
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
	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			kitten::K_GameObject* testTile = m_pTileList[x][z];

			kitten::Transform& transform = testTile->getTransform();
			transform.setParent(&m_attachedObject->getTransform());
			transform.setIgnoreParent(true);
		}
	}

	// PowerTracker component attached to Board GO
	kitten::K_Component* powerTracker = kitten::K_ComponentManager::getInstance()->createComponent("PowerTracker");
	m_attachedObject->addComponent(powerTracker);
}

void BoardCreator::update()
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
	unhighlightTiles(kitten::Event::EventType::Unhighlight_Tile, nullptr);

	if (!m_toBeHighlighted.empty())
	{
		auto it = m_toBeHighlighted.cbegin();
		for (; it != m_toBeHighlighted.cend(); ++it)
		{
			tile = m_pTileList[it->first][it->second];

			kitten::QuadRenderable* quad = tile->getComponent<kitten::QuadRenderable>();
			quad->setColorTint(glm::vec4(0.0f, 0.0f, 0.5f, 1.0f) + quad->getColorTint());

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
	if (p_data->getString("use") == "move")
	{
		m_toBeHighlighted = Range::getTilesInRange(
			p_data->getGameObj("tileAtOrigin"),
			p_data->getInt("minRange"),
			p_data->getInt("maxRange"),
			m_pTileList);
	} else
	{
		m_toBeHighlighted = *p_data->getTileList();
	}
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

void BoardCreator::unhighlightCurrent(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	if (!m_lastHighlighted.empty())
	{
		m_toBeUnhighlighted = m_lastHighlighted;
		m_lastHighlighted.clear();
	}
}

kitten::K_GameObject * BoardCreator::getTile(int x, int z)
{
	kitten::K_GameObject * t = m_pTileList[x][z];
	return t;
}
