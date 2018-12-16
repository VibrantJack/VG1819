#include "BoardManager.h"
#include "kitten\event_system\EventManager.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"
#include <sstream>

BoardManager* BoardManager::sm_instance = nullptr;

void BoardManager::setSpawnPoint(kitten::Event::TileList p_list)
{
	m_spawnPointList = p_list;
}

kitten::K_GameObject* BoardManager::getSpawnPoint(int m_clientId)
{
	kitten::K_GameObject* tile;
	if (m_clientId > -1 && m_clientId < m_spawnPointList.size())
	{
		std::pair<int, int> point = m_spawnPointList[m_clientId];
		tile = getTile(point.first, point.second);
	}
	else
	{
		std::pair<int, int> point = m_spawnPointList.back();
		tile = getTile(point.first, point.second);
		m_spawnPointList.pop_back();
	}

	return tile;
}

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
		if (m_select)
		{
			m_select = false;
			m_selectRepeat = false;
			m_selectNum = 0;
			m_targetNum = 0;
			m_highlighter->unhighlightAll(TileInfo::Select);
			return m_selectList;
		}
		else
		{
			return m_areaList;
		}
	}
	
	return kitten::Event::TileList();
}

void BoardManager::select()
{
	if (m_select && m_area->isActive())
	{
		m_selectNum++;
		//add area list to select list
		for (int i = 0; i < m_areaList.size(); i++)
		{
			std::pair<int, int> pos = m_areaList[i];

			if (m_selectRepeat)//allow duplicate
			{
				m_selectList.push_back(pos);
			}
			else
			{
				//check duplicate
				bool repeat = false;
				for (int j = 0; j < m_selectList.size(); j++)
				{
					if (pos == m_selectList[j])
					{
						repeat = true;
						break;
					}
				}
				if (repeat)//ignore repeat
					continue;
				else
					m_selectList.push_back(pos);
			}
		}

		m_highlighter->highlightTile(TileInfo::Select, m_selectList);
	}
}

void BoardManager::deselect()
{
	if (m_select && m_area->isActive())
	{
		m_selectNum--;
		//remove area list from select list
		for (int i = 0; i < m_areaList.size(); i++)
		{
			std::pair<int, int> pos = m_areaList[i];

			auto it = m_selectList.begin();
			while (it != m_selectList.end())
			{
				if (*it == pos)
				{
					it = m_selectList.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
		m_highlighter->unhighlightTile(TileInfo::Select, m_areaList);
	}
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

void BoardManager::tileClicked(bool p_send)
{
	if (p_send)
	{
		if (m_select)
		{
			select();

			if (m_selectNum < m_targetNum)//dont have enough selected target
				return;
		}

		kitten::Event* e = new kitten::Event(kitten::Event::Tile_Clicked);

		e->putInt("highlighted", TRUE);

		kitten::Event::TileList list = getArea();
		e->putInt(TILE_NUMBER, list.size());

		for (int i = 0; i < list.size(); i++)
		{
			int x = list[i].first;
			int z = list[i].second;
			kitten::K_GameObject* tileGO = getTile(x, z);

			std::stringstream stm;
			stm << TILE << i;
			std::string key = stm.str();

			e->putGameObj(key, tileGO);
		}

		m_highlighter->unhighlightAll(TileInfo::Range);

		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Tile_Clicked, e);
	}
	else
	{
		kitten::Event* e = new kitten::Event(kitten::Event::Tile_Clicked);
		e->putInt("highlighted", FALSE);
		getArea();
		m_highlighter->unhighlightAll(TileInfo::Range);
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Tile_Clicked, e);
	}
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

	m_select = false;
	m_selectRepeat = false;
	m_selectNum = 0;
	m_targetNum = 0;
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
	else if (p_data->getString("mode") == ABILITY_MANIPULATE_TILE)
	{
		const kitten::Event::TileList* l = p_data->getTileList();
		m_highlighter->highlightTile(TileInfo::Owned, *l);
		return;
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
	//select
	m_selectList.clear();
	m_selectList.shrink_to_fit();//reset list

	if (p_data->getInt("select") == TRUE)
	{
		m_select = true;
		m_targetNum = p_data->getInt("target");
		if (p_data->getInt("repeat") == TRUE)
		{
			m_selectRepeat = true;
		}
		else
		{
			m_selectRepeat = false;
		}
	}

	//area
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
