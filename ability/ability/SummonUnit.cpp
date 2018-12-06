// SummonUnit
//
// Handles the SummonUnit ability used by Commanders
//
// @Ken

#include "ability\ability\Ability.h"
#include "kitten\event_system\EventManager.h"
#include "unit\Unit.h"
#include "unit/unitComponent/UnitMove.h"
#include "components/PowerTracker.h"
#include "board/BoardManager.h"
#include "unit/UnitSpawn.h"
#include "kitten/K_GameObjectManager.h"
#include "kibble/databank/databank.hpp"

namespace ability
{
	SummonUnit::SummonUnit()
	{

	}

	int SummonUnit::effect(AbilityInfoPackage* p_info)
	{

		PowerTracker* powerTracker = BoardManager::getInstance()->getPowerTracker();

		//get Unit data
		//fixed for now
		unit::Unit* u = kibble::getUnitFromId(2);
		if (u->m_attributes[UNIT_COST] <= powerTracker->getCurrentPower())
		{
			kitten::K_GameObject* uGO = unit::UnitSpawn::getInstanceSafe()->spawnUnitObject(2);

			powerTracker->summonUnitCost(u->m_attributes[UNIT_COST]);

			kitten::K_GameObject* tile = p_info->m_targetTilesGO[0];
			uGO->getComponent<unit::UnitMove>()->setTile(tile);
		}

		/*
		kitten::Event* p_data = new kitten::Event(kitten::Event::EventType::Highlight_Tile);
		//p_data->putTileList(&p_info->m_targetTiles);
		p_data->putString(TILE_OWNER_KEY, p_info->m_source->m_ID);
		p_data->putGameObj("tileAtOrigin", p_info->m_source->getTile());
		p_data->putString("mode", "range");
		p_data->putString("use", "summon");
		p_data->putInt("min_range",1);
		p_data->putInt("max_range", 1);
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Highlight_Tile, p_data);
		*/

		//delete package
		delete p_info;

		return 0;
	}
}