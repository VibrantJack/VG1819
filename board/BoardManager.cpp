#include "BoardManager.h"
#include "kitten\event_system\EventManager.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"
#include <sstream>

BoardManager* BoardManager::sm_instance = nullptr;

void BoardManager::setTileList(std::vector<kitten::K_GameObject*> p_list)
{
	m_tileList = p_list;
}

void BoardManager::setDimension(int p_x, int p_z)
{
	m_dimension = std::pair<int, int>(p_x, p_z);
	m_range->setDimension(p_x, p_z);
}

std::pair<int, int> BoardManager::getDimension()
{
	return m_dimension;
}

kitten::K_GameObject * BoardManager::getTile(int p_x, int p_z)
{
	std::pair<int, int> pos(p_x, p_z);
	int z_length = m_dimension.second;
	if (pos == m_tileList[p_x * z_length + p_z]->getComponent<TileInfo>()->getPos())
	{
		return m_tileList[p_x * z_length + p_z];
	}
	assert(false);//not found tile or wrong in position
	return nullptr;
}

void BoardManager::showArea(kitten::K_GameObject* p_pivot)
{
	if (m_area->isActive())
	{
		hideArea();

		m_areaList = m_area->getTileListWithPivot(p_pivot);
		applyFilter(&m_areaList);

		m_highlighter->highlightTile(TileInfo::Area, m_areaList);
	}
}

void BoardManager::hideArea()
{
	if (m_area->isActive())
	{
		m_highlighter->unhighlightAll(TileInfo::Area);
	}
}

kitten::Event::TileList BoardManager::getArea()
{
	if (m_area->isActive())
	{
		m_area->removePattern();
		m_highlighter->unhighlightAll(TileInfo::Area);
		return m_areaList;
	}
	
	return kitten::Event::TileList();
}

kitten::Event::TileList BoardManager::getRange()
{
	return m_rangeList;
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

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Set_Area_Pattern,
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
	m_pipeline = new TilePipeline();
	m_area = new Area();
	//m_pathFind = new PathFind();
	registerEvent();
}

BoardManager::~BoardManager()
{
	delete m_range;
	delete m_highlighter;
	delete m_pipeline;
	delete m_area;
	//delete m_pathFind;
}

void BoardManager::listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	switch (p_type)
	{
	case kitten::Event::Highlight_Tile:
		highlightTile(p_data);
		break;
	case kitten::Event::Unhighlight_Tile:
		m_highlighter->unhighlightAll(TileInfo::Range);
		break;
	case kitten::Event::Set_Area_Pattern:
		setArea(p_data);
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

	//apply filter
	setFilter(FILTER, p_data);
	applyFilter(&list);
  
	m_rangeList = list;

	m_highlighter->highlightTile(TileInfo::Range, list);
}

/*
void BoardManager::unhighlightTile(kitten::Event * p_data)
{
	m_highlighter->unhighlightAll(TileInfo::ForRange);
}
*/

void BoardManager::setFilter(const std::string & p_filter, kitten::Event * p_data)
{
	int filterNum = p_data->getInt(p_filter);
	m_pipeline->resetFilter();

	kitten::K_GameObject* origin = p_data->getGameObj("tileAtOrigin");
	kitten::K_GameObject* ugo = origin->getComponent<TileInfo>()->getUnit();
	m_pipeline->setSource(ugo->getComponent<unit::Unit>());
	for (int i = 0; i < filterNum; i++)
	{
		std::stringstream stm;
		stm << p_filter << i;
		std::string fkey = stm.str();
		m_pipeline->useFilter(p_data->getString(fkey));
	}
}

void BoardManager::applyFilter(kitten::Event::TileList * p_list)
{
	m_pipeline->filterList(p_list);
}

void BoardManager::setArea(kitten::Event * p_data)
{
	m_area->setPattern(p_data);

	setFilter(AREA_FILTER, p_data);

	kitten::K_GameObject* p = p_data->getGameObj(ORIGIN);

	//show inital highlight
	TileInfo* info = p->getComponent<TileInfo>();
	if (info->isHighlighted(TileInfo::Range))
	{
		showArea(p);
	}

}
