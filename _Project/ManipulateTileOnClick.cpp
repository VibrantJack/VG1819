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
#include "TileInfo.h"
#include "kitten\K_GameObject.h"

#include "kitten\event_system\EventManager.h"

ManipulateTileOnClick::ManipulateTileOnClick()
{

}

ManipulateTileOnClick::~ManipulateTileOnClick()
{

}

void ManipulateTileOnClick::onClick()
{
	if (ability::AbilityManager::getInstance()->lastAbilityUsed() == MANIPULATE_TILE_ABILITY)
	{
		TileInfo* tileInfo = m_attachedObject->getComponent<TileInfo>();
		if (tileInfo->isHighlighted() && tileInfo->getOwnerId() == "NONE")
		{
			tileInfo->setOwnerId(tileInfo->getHighlightedBy());
			kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Unhighlight_Tile, nullptr);
		}
		else
		{
			kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Unhighlight_Tile, nullptr);
		}
	}
}