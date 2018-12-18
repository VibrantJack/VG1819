#include "SpawnUnitOnDrop.h"
#include "unit/Unit.h"
#include "unit/UnitSpawn.h"
#include "kitten/InputManager.h"
#include "board/tile/TileInfo.h"
#include "unit/unitComponent/UnitMove.h"
#include "kitten/K_GameObjectManager.h"
#include <iostream>

void SpawnUnitOnDrop::onDrop()
{
	int unitId = 1; // default
	// TODO add whatever check it needs to update the unitID above to spawn.

	// Check if it's a tile
	kitten::K_GameObject* targetTile = input::InputManager::getInstance()->getMouseClosesHit();
	if (targetTile == nullptr || targetTile->getComponent<TileInfo>() == nullptr
		|| targetTile->getComponent<TileInfo>()->hasUnit())
	{
		DragNDrop::onDrop();
		return;
	}

	// TODO add all limitations before the spawning here! 

	// Generate Unit and set Tile
	unit::UnitSpawn::getInstanceSafe()->spawnUnitObject(unitId)->getComponent<unit::UnitMove>()->setTile(targetTile);

	// Delete Card
	kitten::K_GameObjectManager::getInstance()->destroyGameObject(this->m_attachedObject);
}