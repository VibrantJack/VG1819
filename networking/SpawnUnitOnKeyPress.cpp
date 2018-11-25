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
#include "unit/UnitTest.h"

#include "unit\InitiativeTracker\InitiativeTracker.h"

// Networking stuf
#include "networking\NetworkData.h"

SpawnUnitOnKeyPress::SpawnUnitOnKeyPress()
	:
	m_bUnitsSpawned(false),
	m_bGameStarted(false)
{
	unit::UnitSpawn::getInstanceSafe();
}

SpawnUnitOnKeyPress::~SpawnUnitOnKeyPress()
{

}

void SpawnUnitOnKeyPress::start()
{
	
}

void SpawnUnitOnKeyPress::update()
{
	if (networking::ClientGame::isNetworkValid() && !unit::UnitTest::isTested())
	{		
		if (input::InputManager::getInstance()->keyDown('S') && !input::InputManager::getInstance()->keyDownLast('S') && !m_bUnitsSpawned)
		{
			m_client = networking::ClientGame::getInstance();
			int clientId = m_client->getClientId();
			if (clientId == 0)
			{
				int posX = 7;
				int posY = 4;
				int unitId = 1;

				for (int i = 0; i < 5; ++i)
				{
					m_client->summonUnit(clientId, unitId, posX, posY);
					m_client->sendSummonUnitPacket(clientId, unitId, posX, posY);
					posX++;
					unitId++;
					if (unitId == 5)
						unitId++;
				}
				m_bUnitsSpawned = true;
			} 
			else if (clientId == 1)
			{
				int posX = 7;
				int posY = 6;
				int unitId = 1;

				for (int i = 0; i < 5; ++i)
				{
					m_client->summonUnit(clientId, unitId, posX, posY);
					m_client->sendSummonUnitPacket(clientId, unitId, posX, posY);
					posX++;
					unitId++;
					if (unitId == 5)
						unitId++;
				}
				m_bUnitsSpawned = true;		
			}
		}

		if (input::InputManager::getInstance()->keyDown('G') && !input::InputManager::getInstance()->keyDownLast('G') && !m_bGameStarted)
		{
			unit::InitiativeTracker::getInstance()->gameTurnStart();
			m_bGameStarted = true;
		}
	}
}