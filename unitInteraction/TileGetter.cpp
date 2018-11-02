#include "TileGetter.h"
#include <iostream>
#include <sstream>

TileGetter::TileGetter()
{
}

TileGetter::~TileGetter()
{
}

void TileGetter::requireTile(unit::AbilityDescription * p_ad, unit::Unit* p_source, bool p_needUnit)
{
	//set
	m_ad = p_ad;
	m_source = p_source;
	m_needUnit = p_needUnit;

	//initialize
	m_targetNum = 0;
	m_tileList.clear();
	m_tileList.shrink_to_fit();
	m_unitList.clear();
	m_unitList.shrink_to_fit();

	triggerHighlightEvent();
	registerEvent();//ready to receive response
}

void TileGetter::registerEvent()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Tile_Clicked,
		this,
		std::bind(&TileGetter::listenEvent, this, std::placeholders::_1, std::placeholders::_2));
}

void TileGetter::deregisterEvent()
{
	kitten::EventManager::getInstance()->queueRemoveListener(kitten::Event::Tile_Clicked, this);
}

void TileGetter::listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	if (m_targetNum >= m_ad->m_intValue["target"])
		return;

	if (p_type == kitten::Event::Tile_Clicked)
	{
		bool highlighted = p_data->getInt("highlighted");
		if (highlighted)
		{
			getTiles(p_data);
		}
		else//cancel
		{
			cancel();
		}
	}
	
}

void TileGetter::getTiles(kitten::Event * p_data)
{
	int tnum = p_data->getInt("tile_number");//get total number of tiles in event
	for (int i = 0; i < tnum; i++)
	{
		std::stringstream stm;
		stm << "tile" << i;
		std::string tkey = stm.str();
		kitten::K_GameObject* tileGO = p_data->getGameObj(tkey);//find each tile

		m_tileList.push_back(tileGO);
		if (m_needUnit)
			getUnit(tileGO);
	}
	m_targetNum++;
	//check if player need to click more tiles
	if (m_targetNum >= m_ad->m_intValue["target"])
	{
		send();
	}
	else
	{//get more
		triggerHighlightEvent();
		registerEvent();
	}
}

void TileGetter::getUnit(kitten::K_GameObject * p_tile)
{
	TileInfo* info = p_tile->getComponent<TileInfo>();
	if (info->hasUnit())//if the tile has unit, push it into package
	{
		unit::Unit* u = info->getUnit()->getComponent<unit::Unit>();

		m_unitList.push_back(u);
	}
}

void TileGetter::triggerHighlightEvent()
{
	//trigger highlight tile event

	//normal range
	kitten::Event* e = new kitten::Event(kitten::Event::Highlight_Tile);
	putRange(e);
	putFilter(e);
	
	//TO DO: area

	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Highlight_Tile, e);
}

void TileGetter::putRange(kitten::Event * e)
{
	if (m_ad->m_intValue.find("min_range") != m_ad->m_intValue.end())
	{
		e->putString("mode", "range");
		e->putGameObj("tileAtOrigin", m_source->getTile());
		e->putInt("min_range", m_ad->m_intValue["min_range"]);
		e->putInt("max_range", m_ad->m_intValue["max_range"]);
	}
	else
	{
		e->putString("mode", "all");
	}
}

void TileGetter::putFilter(kitten::Event * e)
{
	if (m_ad->m_intValue.find("filter") != m_ad->m_intValue.end())
	{
		int filterNum = m_ad->m_intValue["filter"];
		e->putInt("filter", filterNum);
		for (int i = 0; i < filterNum; i++)
		{
			std::stringstream stm;
			stm << "filter" << i;
			std::string fkey = stm.str();
			e->putString(fkey, m_ad->m_stringValue[fkey]);
		}
	}
	else
	{
		e->putInt("filter", 0);
	}
}

void TileGetter::triggerUnhighlightEvent()
{
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Unhighlight_Tile, nullptr);
}

void TileGetter::send()
{
	deregisterEvent();
	UnitInteractionManager::getInstance()->setTarget(m_tileList,m_unitList);
}

void TileGetter::cancel()
{
	deregisterEvent();
	//triggerUnhighlightEvent();
	UnitInteractionManager::getInstance()->cancel();
}
