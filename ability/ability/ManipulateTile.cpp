// ManipulateTile
// 
// Sprint #2 - First implementation of ManipulateTile ability
// Gets the target tile position and changes its colour
//
// @Ken

#include "ability\ability\Ability.h"
#include "kitten\event_system\EventManager.h"
#include "unit\Unit.h"

namespace ability
{
	ManipulateTile::ManipulateTile()
	{
	}

	ManipulateTile::~ManipulateTile()
	{
	}

	int ManipulateTile::effect(const AbilityInfoPackage* p_info)
	{
		kitten::Event* p_data = new kitten::Event(kitten::Event::EventType::Highlight_Tile);
		p_data->putTileList(&p_info->m_targetTilesPos);
		p_data->putString(TILE_OWNER_KEY, p_info->m_source->m_ID);
		p_data->putString("mode", "all");
		p_data->putString("use", "ManipulateTile");//different from other 
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Highlight_Tile, p_data);

		//delete package
		delete p_info;

		return 0;
	}

}
