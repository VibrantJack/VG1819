#include "Commander.h"
#include "unitInteraction/UnitInteractionManager.h"

namespace unit
{
	unit::Commander::Commander()
	{
	}

	unit::Commander::~Commander()
	{
		//delete m_adSpawn;
		delete m_adTile;
	}

	void Commander::init()
	{
		m_adSpawn = new unit::AbilityDescription();
		m_adSpawn->m_stringValue["name"] = SUMMON_UNIT_ABILITY;
		m_adSpawn->m_intValue["target"] = 1;
		//range
		m_adSpawn->m_intValue["min_range"] = 1;
		m_adSpawn->m_intValue["max_range"] = 1;
		//filter
		m_adSpawn->m_intValue["filter"] = 1;
		m_adSpawn->m_stringValue["filter0"] = "unit";

		m_adTile = new unit::AbilityDescription();
		m_adTile->m_stringValue["name"] = MANIPULATE_TILE_ABILITY;
		m_adTile->m_intValue["target"] = 1;
		//filter
		m_adTile->m_intValue["filter"] = 1;
		m_adTile->m_stringValue["filter0"] = "owned_tile";
	}

	void Commander::manipulateTile()
	{
		UnitInteractionManager::getInstance()->request(this, m_adTile);
	}

	void Commander::spawnUnit()
	{
		UnitInteractionManager::getInstance()->request(this, m_adSpawn);
	}
}

