// SummonUnit
//
// Handles the SummonUnit ability used by Commanders
//
// @Ken

#include "ability\ability\Ability.h"
#include "kitten\event_system\EventManager.h"
#include "unit\Unit.h"

namespace ability
{
	SummonUnit::SummonUnit()
	{

	}

	int SummonUnit::effect(const AbilityInfoPackage* p_info)
	{

		kitten::Event* p_data = new kitten::Event(kitten::Event::EventType::Highlight_Tile);
		p_data->putTileList(&p_info->m_targetTiles);
		p_data->putString(TILE_OWNER_KEY, p_info->m_source->m_ID);
		p_data->putString("mode", "range");
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Highlight_Tile, p_data);
		return 0;
	}
}