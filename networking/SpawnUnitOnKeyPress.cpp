// SpawnUnitOnKeyPress
//
// Used to spawn a unit on a key press to test with networking code
// 
// @Ken

#include "networking\SpawnUnitOnKeyPress.h"
#include "kitten\InputManager.h"

#include "kitten/K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"
#include "kibble/databank/databank.hpp"

// Unit stuff
#include "unit/unitComponent/UnitMove.h"
#include "unit\UnitMonitor.h"
#include "unit\UnitSpawn.h"

#include "unit\InitiativeTracker\InitiativeTracker.h"

// Networking stuff
#include "networking\ClientGame.h"
#include "networking\NetworkData.h"

SpawnUnitOnKeyPress::SpawnUnitOnKeyPress()
	:
	m_iUnitId(6)
{
	unit::UnitSpawn::getInstanceSafe();
}

SpawnUnitOnKeyPress::~SpawnUnitOnKeyPress()
{

}

void SpawnUnitOnKeyPress::update()
{
	if (input::InputManager::getInstance()->keyDown('S') && !input::InputManager::getInstance()->keyDownLast('S'))
	{
		int posX = 4;
		int posY = 4;
		
		if (networking::ClientGame::getInstance())
		{
			networking::ClientGame::getInstance()->summonUnit(networking::ClientGame::getInstance()->getClientId(), m_iUnitId, posX, posY);
			networking::ClientGame::getInstance()->sendSummonUnitPacket(networking::ClientGame::getInstance()->getClientId(), m_iUnitId, posX, posY);
		}
		m_iUnitId = 2;
	}

	if (input::InputManager::getInstance()->keyDown('G') && !input::InputManager::getInstance()->keyDownLast('G'))
	{
		unit::InitiativeTracker::getInstance()->gameTurnStart();
	}
}