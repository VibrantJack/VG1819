#include "TileGetter.h"
#include <iostream>
#include <sstream>

TileGetter::TileGetter()
{
	m_reg = false;
	m_respond = false;
}

TileGetter::~TileGetter()
{
}

void TileGetter::requireTile(unit::AbilityDescription * p_ad, unit::Unit* p_source, bool p_needUnit)
{
	if (!m_reg)
	{
		registerEvent();
		m_reg = true;
	}

	//set
	m_ad = p_ad;
	m_source = p_source;
	m_needUnit = p_needUnit;

	//initialize
	//m_targetNum = 0;
	m_tileList.clear();
	m_tileList.shrink_to_fit();
	m_unitList.clear();
	m_unitList.shrink_to_fit();

	triggerHighlightEvent();
	m_respond = true;
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
	if (!m_respond)
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
	int tnum = p_data->getInt(TILE_NUMBER);//get total number of tiles in event

	if (tnum == 0)
	{
		cancel();
		return;
	}

	for (int i = 0; i < tnum; i++)
	{
		std::stringstream stm;
		stm << TILE << i;
		std::string tkey = stm.str();
		kitten::K_GameObject* tileGO = p_data->getGameObj(tkey);//find each tile

		m_tileList.push_back(tileGO);
		getUnit(tileGO);
	}

	send();

	/* target check is move to board manager
	m_targetNum++;
	//check if player need to click more tiles
	if (m_targetNum >= m_ad->m_intValue["target"])
	{
		send();
	}
	else
	{//get more
		triggerHighlightEvent();
	}*/
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
	putFilter("filter", e);
	//move mode
	if (m_ad->m_stringValue["name"] == ACTION_MOVE)
		e->putInt("path", TRUE);
	else
		e->putInt("path", FALSE);

	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Highlight_Tile, e);

	//area
	e = new kitten::Event(kitten::Event::Set_Area_Pattern);
	putArea(e);
	putFilter("area_filter", e);

	//select mode
	int t = m_ad->m_intValue["target"];
	if (t > 1)
	{
		e->putInt("select", TRUE);
		e->putInt("target", t);
		if (m_ad->m_stringValue["select_repeat"] == "true")
			e->putInt("repeat", TRUE);
		else
			e->putInt("repeat", FALSE);
	}
	else
		e->putInt("select", FALSE);

	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Set_Area_Pattern, e);
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
		e->putGameObj("tileAtOrigin", m_source->getTile());
	}
}

void TileGetter::putFilter(const std::string & p_filter, kitten::Event * e)
{
	if (m_ad->m_intValue.find(p_filter) != m_ad->m_intValue.end())
	{
		int filterNum = m_ad->m_intValue[p_filter];
		e->putInt(p_filter, filterNum);
		for (int i = 0; i < filterNum; i++)
		{
			std::stringstream stm;
			stm << p_filter << i;
			std::string fkey = stm.str();
			e->putString(fkey, m_ad->m_stringValue[fkey]);
		}
	}
	else
	{
		e->putInt(p_filter, 0);
	}
}

void TileGetter::putArea(kitten::Event * e)
{
	e->putGameObj("tileAtOrigin", m_source->getTile());

	const std::unordered_map<std::string, int> &iv = m_ad->m_intValue;
	const std::unordered_map<std::string, std::string> &sv = m_ad->m_stringValue;

	if (sv.find(AREA_MODE) != sv.end())
	{
		if(iv.find(AREA_FIX) != iv.end())
			e->putInt(AREA_FIX, iv.at(AREA_FIX));
		else
			e->putInt(AREA_FIX, FALSE);
		e->putString(AREA_MODE,sv.at(AREA_MODE));

		if (iv.find(AREA_LEN) != iv.end())
			e->putInt(AREA_LEN, iv.at(AREA_LEN));
		else if (iv.find(AREA_MIN) != iv.end())
		{
			e->putInt(AREA_MIN, iv.at(AREA_MIN));
			e->putInt(AREA_MAX, iv.at(AREA_MAX));
		}
	}
	else//default : point pattern
	{
		e->putInt(AREA_FIX, FALSE);
		e->putString(AREA_MODE, POINT_AREA);
	}
	
}

void TileGetter::triggerUnhighlightEvent()
{
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Unhighlight_Tile, nullptr);
}

void TileGetter::send()
{
	m_respond = false;
	if (m_needUnit && m_unitList.empty())
		cancel();
	else
		UnitInteractionManager::getInstance()->setTarget(m_tileList,m_unitList);
}

void TileGetter::cancel()
{
	//deregisterEvent();
	triggerUnhighlightEvent();
	m_respond = false;
	UnitInteractionManager::getInstance()->cancel();
}
