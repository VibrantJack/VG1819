#include "SpawnUnitOnDrop.h"
#include "unit/Unit.h"
#include "unit/UnitSpawn.h"
#include "kitten/InputManager.h"
#include "board/tile/TileInfo.h"
#include "unit/unitComponent/UnitMove.h"
#include "kitten/K_GameObjectManager.h"
#include "kibble/databank/databank.hpp"
#include "components/PowerTracker.h"
#include "board/BoardManager.h"
#include <iostream>

void SpawnUnitOnDrop::onDrop()
{
	// Check if we hit something
	kitten::K_GameObject* targetTile = input::InputManager::getInstance()->getMouseLastHitObject();
	if (targetTile == nullptr  // No Target
		|| targetTile->getComponent<TileInfo>() == nullptr // Target isn't a tile
		|| targetTile->getComponent<TileInfo>()->hasUnit() // Target tile already has a unit on it
		)
	{
		DragNDrop::onDrop();
		return;
	}
	
	// Unit setup
	unit::Unit* unit = m_attachedObject->getComponent<unit::Unit>();
	if (unit == nullptr) unit = kibble::getUnitFromId(1); // basically defaults to a priest. TODO remove this line when hand fully functional.

	// Check for unit stuff.
	if(BoardManager::getInstance()->getPowerTracker()->getCurrentPower() < unit->m_attributes[UNIT_COST] // Check if there is enough power to spawn this.
		)
	{
		DragNDrop::onDrop();
		return;
	}

	// Update Power Tracker
	BoardManager::getInstance()->getPowerTracker()->summonUnitCost(unit->m_attributes[UNIT_COST]);

	// Generate Unit and set Tile
	unit::UnitSpawn::getInstance()->spawnUnitObject(unit)->getComponent<unit::UnitMove>()->setTile(targetTile);

	// Delete Card
	kitten::K_GameObjectManager::getInstance()->destroyGameObjectWithChild(this->m_attachedObject);
}

void SpawnUnitOnDrop::onHoverEnd() {
	if (!m_isDragging)
	{
		getTransform().place2D(m_origin.x, m_origin.y);
	}
}

void SpawnUnitOnDrop::onHoverStart() {
	if (!m_isDragging)
	{
		getTransform().place2D(m_origin.x, m_origin.y + 50);
	}
}