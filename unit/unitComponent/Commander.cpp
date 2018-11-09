#include "Commander.h"
#include "unitInteraction/UnitInteractionManager.h"

namespace unit
{
	unit::Commander::Commander()
	{
	}

	unit::Commander::~Commander()
	{
		delete m_adSpawn;
		delete m_adTile;
	}

	void Commander::init(Unit* p_u)
	{
		m_unit = p_u;

		m_adSpawn = new unit::AbilityDescription();
		m_adSpawn->m_stringValue["name"] = ABILITY_SUMMON_UNIT;
		m_adSpawn->m_intValue["target"] = 1;
		//range
		m_adSpawn->m_intValue["min_range"] = 1;
		m_adSpawn->m_intValue["max_range"] = 1;
		//filter
		m_adSpawn->m_intValue["filter"] = 1;
		m_adSpawn->m_stringValue["filter0"] = "unit";

		m_adTile = new unit::AbilityDescription();
		m_adTile->m_stringValue["name"] = ABILITY_MANIPULATE_TILE;
		m_adTile->m_intValue["target"] = 1;
		//filter
		m_adTile->m_intValue["filter"] = 1;
		m_adTile->m_stringValue["filter0"] = "owned_tile";
	}

	void Commander::manipulateTile()
	{
		UnitInteractionManager::getInstance()->request(m_unit, m_adTile);
	}

	void Commander::spawnUnit()
	{
		UnitInteractionManager::getInstance()->request(m_unit, m_adSpawn);
	}
}

