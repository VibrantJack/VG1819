#include "UnitInteractionManager.h"

UnitInteractionManager* UnitInteractionManager::sm_instance = nullptr;

void UnitInteractionManager::request(unit::Unit* p_unit, unit::AbilityDescription * p_ad)
{
	m_ad = p_ad;
	m_abilityName = m_ad->m_stringValue["name"];
	getTile();
}

UnitInteractionManager::UnitInteractionManager()
{
}

UnitInteractionManager::~UnitInteractionManager()
{
	if (m_package != nullptr)
		delete m_package;
}

void UnitInteractionManager::getTile()
{
	//register event for feedback
	registerEvent();

	//trigger highlight tile event
	kitten::Event* e = new kitten::Event(kitten::Event::Highlight_Tile);
	if (m_ad->m_intValue.find("min_range") != m_ad->m_intValue.end())
	{
		e->putString("mode", "range");
		e->putGameObj("tileAtOrigin", m_package->m_source->getTile());
		e->putInt("min_range", m_ad->m_intValue["min_range"]);
		e->putInt("max_range", m_ad->m_intValue["max_range"]);
	}
	e->putString("use", "ability");
	//TO DO: area 
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Highlight_Tile, e);

	
}

void UnitInteractionManager::send()
{
	if (m_gotTarget)
	{
		ability::AbilityManager::getInstance()->useAbility(m_abilityName,m_package);
	}
}

void UnitInteractionManager::registerEvent()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Tile_Clicked,
		this,
		std::bind(&UnitInteractionManager::listenEvent, this, std::placeholders::_1, std::placeholders::_2));
}

void UnitInteractionManager::deregisterEvent()
{
	kitten::EventManager::getInstance()->queueRemoveListener(kitten::Event::Tile_Clicked, this);

	//trigger unhighlight event
	kitten::Event* e = new kitten::Event(kitten::Event::Unhighlight_Tile);
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Unhighlight_Tile, e);
}

void UnitInteractionManager::listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	if (p_type == kitten::Event::Tile_Clicked)
	{
		bool highlighted = p_data->getInt("highlighted");
		if (highlighted)
		{
			int tnum = p_data->getInt("tile_number");//get total number of tiles in event
			for (int i=0; i<tnum; i++)
			{
				std::string tkey = "tile" + i;
				kitten::K_GameObject* tileGO = p_data->getGameObj(tkey);//find each tile
				TileInfo* info = tileGO->getComponent<TileInfo>();
				if (info->hasUnit())//if the tile has unit, push it into package
				{
					unit::Unit* u = info->getUnit()->getComponent<unit::Unit>();
					m_package->m_targets.push_back(u);
				}
			}
			m_target++;
			//check if player need to click more tiles
			if (m_target >= m_ad->m_intValue["target"])
			{
				m_gotTarget = true;
				deregisterEvent();
				send();
			}
		}
		else//cancel
		{
			cancel();
		}
	}
}
