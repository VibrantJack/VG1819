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
	m_iUnitId(0)
{

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
			networking::ClientGame::getInstance()->summonUnit(networking::ClientGame::getClientId(), m_iUnitId, posX, posY);

			SummonUnitPacket* packet = new SummonUnitPacket();
			packet->packetType = PacketTypes::SUMMON_UNIT;
			packet->clientId = networking::ClientGame::getInstance()->getClientId();
			packet->unitId = m_iUnitId;
			packet->posX = posX;
			packet->posY = posY;

			networking::ClientGame::getInstance()->sendPacket(packet);
		}
		else
		{
			kitten::K_GameObject* testDummyGO = unit::UnitSpawn::getInstance()->spawnUnitObject(kibble::getUnitFromId(m_iUnitId));
			unit::Unit* testDummy = testDummyGO->getComponent<unit::Unit>();
			unit::UnitMonitor::getInstanceSafe()->printUnit(testDummy);

			//initialize position
			testDummyGO->getComponent<unit::UnitMove>()->setTile(posX, posY);

			kitten::K_ComponentManager* compMan = kitten::K_ComponentManager::getInstance();
			testDummyGO->addComponent(compMan->createComponent("UseAbilityWhenClicked"));
			testDummyGO->addComponent(compMan->createComponent("SelectAbility"));
		}
		m_iUnitId = (m_iUnitId + 1) % 4;
	}

	if (input::InputManager::getInstance()->keyDown('G') && !input::InputManager::getInstance()->keyDownLast('G'))
	{
		unit::InitiativeTracker::getInstance()->gameTurnStart();
	}
}