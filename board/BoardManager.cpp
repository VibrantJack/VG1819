#include "BoardManager.h"
#include "kitten\event_system\EventManager.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"

BoardManager* BoardManager::sm_instance = nullptr;

void BoardManager::setTileList(std::vector<kitten::K_GameObject*>* p_list)
{
	m_tileList = *p_list;
}

void BoardManager::setDimension(int p_x, int p_z)
{
	m_dimension = std::pair<int, int>(p_x, p_z);
}

kitten::K_GameObject * BoardManager::getTile(int p_x, int p_z)
{
	std::pair<int, int> pos(p_x, p_z);
	int x_length = m_dimension.first;
	if (pos == m_tileList[p_x * x_length + p_z]->getComponent<TileInfo>()->getPos())
	{
		return m_tileList[p_x * x_length + p_z];
	}
	assert(false);//not found tile or wrong in position
	return nullptr;
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
	//m_boardGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
	m_range = new Range();
	m_highlighter = static_cast<Highlighter*>(kitten::K_ComponentManager::getInstance()->createComponent("Highlighter"));

	registerEvent();
}

BoardManager::~BoardManager()
{
	delete m_range;
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
		list = m_range->getTilesInRange(p_data);
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
