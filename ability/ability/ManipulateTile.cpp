// ManipulateTile
// 
// Sprint #2 - First implementation of ManipulateTile ability
// Gets the target tile position and changes its colour
//
// @Ken

#include "ability/ability/Ability.h"
#include "kitten\event_system\EventManager.h"

namespace ability
{
	ManipulateTile::ManipulateTile()
	{
	}

	int ManipulateTile::effect(const AbilityInfoPackage* p_info)
	{
		// Loop through the list of tiles and trigger an event to highlight each one		
		/*auto it = p_info->m_targetTiles.cbegin();
		for (; it != p_info->m_targetTiles.cend(); ++it)
		{
			kitten::Event* p_data = new kitten::Event(kitten::Event::EventType::Highlight_Tile);
			p_data->putInt(TILE_POS_X, it->first);
			p_data->putInt(TILE_POS_Y, it->second);

			kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Highlight_Tile, p_data);
		}*/

		kitten::Event* p_data = new kitten::Event(kitten::Event::EventType::Highlight_Tile);
		p_data->putTileList(&p_info->m_targetTiles);

		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Highlight_Tile, p_data);

		return 0;
	}

}
