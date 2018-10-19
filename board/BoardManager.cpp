#include "BoardManager.h"
#include "kitten\event_system\EventManager.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"

BoardManager* BoardManager::sm_instance = nullptr;

void BoardManager::createBoard(int p_x, int p_z)
{
	m_dimension = std::pair<int, int>(p_x, p_z);
	for (int x = 0; x < p_x; x++)
	{
		for (int z = 0; z < p_z; z++)
		{
			kitten::K_GameObject* tileGO = m_boardCreator->createTile(x, z);
			m_tileList.push_back(tileGO);

			kitten::Transform& transform = tileGO->getTransform();
			transform.setParent(&m_boardGO->getTransform());
			transform.setIgnoreParent(true);
		}
	}

	// PowerTracker component attached to Board GO
	kitten::K_Component* powerTracker = kitten::K_ComponentManager::getInstance()->createComponent("PowerTracker");
	m_boardGO->addComponent(powerTracker);

	registerEvent();
}

kitten::K_GameObject * BoardManager::getTile(int p_x, int p_z)
{
	return m_boardCreator->getTile(p_x,p_z);
}

void BoardManager::registerEvent()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Highlight_Tile,
		this,
		std::bind(&BoardManager::listenEvent, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Unhighlight_Tile,
		this,
		std::bind(&BoardManager::listenEvent, this, std::placeholders::_1, std::placeholders::_2));
	// End adding listeners for events
}

void BoardManager::deregisterEvent()
{
}

BoardManager::BoardManager()
{
	m_boardGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
	m_boardCreator = new BoardCreator();
	m_highlighter = static_cast<Highlighter*>(kitten::K_ComponentManager::getInstance()->createComponent("Highlighter"));
}

BoardManager::~BoardManager()
{
	delete m_boardCreator;
	delete m_highlighter;
}

void BoardManager::listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	switch (p_type)
	{
	case kitten::Event::Highlight_Tile:
		highlightTile(p_data);
		break;
	case kitten::Event::Unhighlight_Tile:
		unhighlightTile(p_data);
		break;
	case kitten::Event::Manipulate_Tile:
		break;
	case kitten::Event::Highlight_Tile_Summon_Unit:
		break;
	case kitten::Event::Summon_Unit:
		break;
	default:
		break;
	}
}

void BoardManager::highlightTile(kitten::Event * p_data)
{
	kitten::Event::TileList list;
	if (p_data->getString("mode") == "range")
	{
		list = Range::getTilesInRange(
			p_data->getGameObj("tileAtOrigin"),
			p_data->getInt("minRange"),
			p_data->getInt("maxRange"),
			m_tileList);
	}
	else if (p_data->getString("mode") == "all")
	{//highlight all tile
		for (int i = 0; i < m_tileList.size(); i++)
		{
			list.push_back(m_tileList[i]->getComponent<TileInfo>()->getPos());
		}
	}

	m_highlighter->highlightTile(list);
}

void BoardManager::unhighlightTile(kitten::Event * p_data)
{
	m_highlighter->unHighlightCurrent();
}
