#include "SpawnUnitOnDrop.h"
#include "unit/Unit.h"
#include "unit/UnitSpawn.h"
#include "kitten/InputManager.h"
#include "board/tile/TileInfo.h"
#include "unit/unitComponent/UnitMove.h"
#include "kitten/K_GameObjectManager.h"
#include "kibble/databank/databank.hpp"
#include "UI/HandFrame.h"
#include "UI/CardUIO.h"
#include "components/PowerTracker.h"
#include "components/clickables/HoverOverCardBehavior.h"
#include "board/BoardManager.h"
#include "kitten\event_system\EventManager.h"
#include <iostream>

// Networking
#include "networking\ClientGame.h"

#define CARD_HOVER_MOVE_TIME 0.2

void SpawnUnitOnDrop::onClick()
{
	if (networking::ClientGame::isNetworkValid())
	{
		if (unit::InitiativeTracker::getInstance()->getCurrentUnitIndex() >= 0)
		{
			unit::Unit* currentUnit = unit::InitiativeTracker::getInstance()->getCurrentUnit()->getComponent<unit::Unit>();
			unit::Unit* clientCommander = networking::ClientGame::getInstance()->getCommander();
			if (currentUnit != clientCommander) return;
		}
	}

	DragNDrop::onClick();

	if (m_isDragging == false)
		m_attachedObject->getComponent<HoverOverCardBehavior>()->setEnabled(true);
	else
		m_attachedObject->getComponent<HoverOverCardBehavior>()->setEnabled(false);
}

void SpawnUnitOnDrop::onDrop()
{
	// Check if we hit something
	kitten::K_GameObject* targetTile = input::InputManager::getInstance()->getMouseLastHitObject();
	kitten::K_GameObject* targetFrame = input::InputManager::getInstance()->getMouseLastHitFrame();
	if (targetTile == nullptr  // No Target
		|| (targetFrame != nullptr && targetFrame != &m_attachedFrame->getGameObject()) // Over UI or our card
		|| targetTile->getComponent<TileInfo>() == nullptr // Target isn't a tile
		|| targetTile->getComponent<TileInfo>()->hasUnit() // Target tile already has a unit on it
		)
	{
		DragNDrop::onDrop();
		return;
	}
	
	// Unit setup
	unit::Unit* unit = m_attachedObject->getComponent<unit::Unit>();

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

	// Send the summoned unit if we're playing multiplayer
	if (networking::ClientGame::isNetworkValid())
	{
		TileInfo* tileInfo = targetTile->getComponent<TileInfo>();
		networking::ClientGame::getInstance()->sendSummonUnitPacket(unit->m_kibbleID, tileInfo->getPosX(), tileInfo->getPosY());
	}

	// Remove Card from hand
	userinterface::CardUIO* cardUIObject = this->m_attachedObject->getComponent<userinterface::CardUIO>();
	userinterface::HandFrame::getActiveInstance()->removeCard((userinterface::UIObject*)cardUIObject);

	// Delete Card
	kitten::K_GameObjectManager::getInstance()->destroyGameObjectWithChild(this->m_attachedObject);
}

void SpawnUnitOnDrop::onPause()
{
	DragNDrop::onDrop();
	m_isDragging = false;
}

SpawnUnitOnDrop::SpawnUnitOnDrop()
	:
	DragNDrop(true)
{

}

SpawnUnitOnDrop::~SpawnUnitOnDrop()
{
}

void SpawnUnitOnDrop::start()
{
	DragNDrop::start();
	setEnabled(!userinterface::HandFrame::getActiveInstance()->isOnDiscardMode());
}