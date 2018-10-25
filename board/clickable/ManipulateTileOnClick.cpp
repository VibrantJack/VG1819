// ManipulateTileOnClick
//
// Manipulates tile when tile is clicked, only if the tile has been
// highlighted and the last ability used is the ManipulateTile ability
//
// Should be generalized to handle all actions pertaining to clicking on tiles
//
// @Ken

#include "ManipulateTileOnClick.h"
#include "ability\AbilityManager.h"
#include "board/tile/TileInfo.h"
#include "kitten\K_GameObject.h"
#include "components\PowerTracker.h"

#include "kitten\event_system\EventManager.h"
#include "kibble\kibble.hpp"
#include "kibble\databank\databank.hpp"
#include "unit\UnitSpawn.h"
#include "unit\InitiativeTracker\InitiativeTracker.h"
#include "unit\unitComponent\UnitMove.h"
#include "board/BoardManager.h"

ManipulateTileOnClick::ManipulateTileOnClick()
{

}

ManipulateTileOnClick::~ManipulateTileOnClick()
{

}

void ManipulateTileOnClick::onClick()
{
	TileInfo* tileInfo = m_attachedObject->getComponent<TileInfo>();
	if (ability::AbilityManager::getInstance()->lastAbilityUsed() == MANIPULATE_TILE_ABILITY)
	{
		if (tileInfo->isHighlighted() && tileInfo->getOwnerId() == "NONE")
		{
			tileInfo->setOwnerId(tileInfo->getHighlightedBy());
			kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Unhighlight_Tile, nullptr);

			kitten::Event* p_data = new kitten::Event(kitten::Event::EventType::Highlight_Tile);
			p_data->putInt(MANIPULATE_TILE_KEY, 1);
			kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Manipulate_Tile, p_data);

			// We successfully used the ability so now reset lastAbilityUsed so this doesn't keep triggering
			ability::AbilityManager::getInstance()->resetLastAbilityUsed();
		}
		else
		{
			kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Unhighlight_Tile, nullptr);

		}
	}
	else if (ability::AbilityManager::getInstance()->lastAbilityUsed() == SUMMON_UNIT_ABILITY)
	{
		if (tileInfo->isHighlighted() && tileInfo->getOwnerId() == tileInfo->getHighlightedBy())
		{
			kitten::K_GameObject* board = &m_attachedObject->getTransform().getParent()->getAttachedGameObject();

			PowerTracker* powerTracker = board->getComponent<PowerTracker>();
			unit::UnitData* unitData = kibble::getUnitFromId(2);
			if (unitData->m_Cost <= powerTracker->getCurrentPower())
			{
				powerTracker->summonUnitCost(unitData->m_Cost);

				kitten::K_GameObject* unit = unit::UnitSpawn::getInstance()->spawnUnitObject(unitData);
				unit->getComponent<unit::UnitMove>()->setTile(BoardManager::getInstance()->getTile(tileInfo->getPosX(), tileInfo->getPosY()));

				// TEMPORARY: Reset game turn in order to dynamically add a new unit
				//unit::InitiativeTracker::getInstance()->gameTurnStart();
			}
			kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Unhighlight_Tile, nullptr);

			// We successfully used the ability so now reset lastAbilityUsed so this doesn't keep triggering
			ability::AbilityManager::getInstance()->resetLastAbilityUsed();
		}
		else
		{
			kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Unhighlight_Tile, nullptr);
		}
	}
	else
	{
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Unhighlight_Tile, nullptr);

	}

	// Rest the last ability used after we've used an ability or canceled it
	ability::AbilityManager::getInstance()->resetLastAbilityUsed();
}