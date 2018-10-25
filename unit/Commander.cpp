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
		m_adSpawn = nullptr;

		m_adTile = new unit::AbilityDescription();
		m_adTile->m_stringValue["name"] = MANIPULATE_TILE_ABILITY;
		m_adTile->m_intValue["target"] = 1;
		//TO DO:filter
	}

	void Commander::manipulateTile()
	{
		UnitInteractionManager::getInstance()->request(this, m_adTile);
	}

	void Commander::spawnUnit()
	{
	}
}

