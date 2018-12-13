#include "UnitTest.h"
#include "ability/node/AbilityNodeManager.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"
#include <iostream>
#include "kibble/kibble.hpp"
#include "kibble/databank/databank.hpp"

// Includes for tile highlighting and manipulating tile
#include "_Project\UseAbilityWhenClicked.h"
//board clickable
#include "board/clickable/PrintWhenClicked.h"
#include "kitten\K_ComponentManager.h"

//Includes for creating spawn tile
#include "unit/unitComponent/UnitMove.h"
#include "kitten/K_GameObjectManager.h"

#include "board/BoardManager.h"
#include "kitten/sprites/SpriteGroup.h"
//Rock
//test the unit data

namespace unit
{
	UnitTest* UnitTest::m_instance = nullptr;
	bool UnitTest::m_bTested = false;

	UnitTest::UnitTest()
	{
	}

	UnitTest * UnitTest::getInstance()
	{
		return m_instance;
	}

	UnitTest * UnitTest::getInstanceSafe()
	{
		if (m_instance == nullptr)
			m_instance = new UnitTest();
		return m_instance;
	}

	void UnitTest::test()
	{
		m_bTested = true;
		//comment for testing IT

		kitten::K_GameObject* uNEWDUMMY = UnitSpawn::getInstanceSafe()->spawnUnitObject(13); // 13 king !!!
		uNEWDUMMY->getComponent<unit::UnitMove>()->setTile(-1, -1);

		kitten::K_GameObject* uNEWDUMMY2 = UnitSpawn::getInstanceSafe()->spawnUnitObject(14); // queen !!!
		uNEWDUMMY2->getComponent<unit::UnitMove>()->setTile(-1, -1);
		/*
		// Testing highlighting tiles and manipulating tiles using testDummy.txt
		{
			kitten::K_GameObject* testDummyGO = UnitSpawn::getInstanceSafe()->spawnUnitObject(0);
			unit::Unit* testDummy = testDummyGO->getComponent<unit::Unit>();
			UnitMonitor::getInstanceSafe()->printUnit(testDummy);

			//initialize position
			testDummyGO->getComponent<unit::UnitMove>()->setTile(4,4);

			//move to unit spawn
			//kitten::K_ComponentManager* compMan = kitten::K_ComponentManager::getInstance();
			//testDummyGO->addComponent(compMan->createComponent("UseAbilityWhenClicked"));
			//testDummyGO->addComponent(compMan->createComponent("SelectAbility"));

			//PrintWhenClicked* printWhenClick = static_cast<PrintWhenClicked*>(compMan->createComponent("PrintWhenClicked"));
			//printWhenClick->setMessage("Test Dummy");
			//testDummyGO->addComponent(printWhenClick);
		}*/
		// End testing selecting spawned unit
		

		/*
		//create test tile for unit spawn
		kitten::K_GameObject* testTile = kitten::K_GameObjectManager::getInstance()->createNewGameObject("tileobj.txt");
		PrintWhenClicked* printWhenClick = static_cast<PrintWhenClicked*>(kitten::K_ComponentManager::getInstance()->createComponent("PrintWhenClicked"));
		printWhenClick->setMessage("spawn tile is clicked");
		testTile->addComponent(printWhenClick);
		kitten::K_Component* clickBox = kitten::K_ComponentManager::getInstance()->createComponent("ClickableBox");
		testTile->addComponent(clickBox);

		testTile->getTransform().place(0.0f, -1.0f, 16.0f);
		//end of test tile
		*/
		
		//set initial position
		kitten::K_GameObject* u0 = UnitSpawn::getInstanceSafe()->spawnUnitObject(1);//priest
		u0->getComponent<unit::UnitMove>()->setTile(1, 2);

		kitten::K_GameObject* u1 = UnitSpawn::getInstanceSafe()->spawnUnitObject(1);//priest
		u1->getComponent<unit::UnitMove>()->setTile(2, 2);

		kitten::K_GameObject* u2 = UnitSpawn::getInstanceSafe()->spawnUnitObject(2);//archer
		u2->getComponent<unit::UnitMove>()->setTile(3, 2);

		kitten::K_GameObject* u3 = UnitSpawn::getInstanceSafe()->spawnUnitObject(3);//duelist
		u3->getComponent<unit::UnitMove>()->setTile(4, 2);

		kitten::K_GameObject* u4 = UnitSpawn::getInstanceSafe()->spawnUnitObject(4);//engineer
		u4->getComponent<unit::UnitMove>()->setTile(5, 2);
		
		kitten::K_GameObject* u5 = UnitSpawn::getInstanceSafe()->spawnUnitObject(7);//pyromancer
		u5->getComponent<unit::UnitMove>()->setTile(6, 2);

		kitten::K_GameObject* u6 = UnitSpawn::getInstanceSafe()->spawnUnitObject(8);//stone slinger
		u6->getComponent<unit::UnitMove>()->setTile(7, 2);

		kitten::K_GameObject* u7 = UnitSpawn::getInstanceSafe()->spawnUnitObject(9);//arrow tower
		u7->getComponent<unit::UnitMove>()->setTile(8, 2);

		kitten::K_GameObject* u8 = UnitSpawn::getInstanceSafe()->spawnUnitObject(10);//armory
		u8->getComponent<unit::UnitMove>()->setTile(9, 2);

		kitten::K_GameObject* u9 = UnitSpawn::getInstanceSafe()->spawnUnitObject(11);//divine status
		u9->getComponent<unit::UnitMove>()->setTile(10, 2);
		
		kitten::K_GameObject* u10 = UnitSpawn::getInstanceSafe()->spawnUnitObject(12);//oligarch
		u10->getComponent<unit::UnitMove>()->setTile(11, 4);
		//u10->getComponent<Unit>()->m_attributes[COUNTER_MONEY] = 4;
		//kitten::K_GameObject* u11 = UnitSpawn::getInstanceSafe()->spawnUnitObject(5);//wall
		//u11->getComponent<unit::UnitMove>()->setTile(12, 2);
		
		//test unit 
		//unit::Unit* u = u1->getComponent<unit::Unit>();
		//UnitMonitor::getInstanceSafe()->printUnit(u);

		//Test Initiative Tracker
		//kitten::K_GameObject* u2 = UnitSpawn::getInstance()->spawnUnitObject(parser->getUnit("Engineer.txt"));
		//kitten::K_GameObject* u3 = UnitSpawn::getInstance()->spawnUnitObject(parser->getUnit("Duelist.txt"));

		UnitMonitor::getInstanceSafe()->printIT();
		InitiativeTracker::getInstance()->gameTurnStart();
		//UnitMonitor::getInstanceSafe()->printIT();
		//InitiativeTracker::getInstance()->removeUnit(u2);
		//UnitMonitor::getInstanceSafe()->printIT();

		//test sprite group
		/*
		kitten::K_GameObjectManager* gm = kitten::K_GameObjectManager::getInstance();
		kitten::K_ComponentManager* cm = kitten::K_ComponentManager::getInstance();

		kitten::K_GameObject* g = gm->createNewGameObject();
		g->getTransform().place(2.0, 0.5, 2.0);

		kitten::K_GameObject* go = gm->createNewGameObject();

		go->addComponent(cm->createComponent("SpriteRenderable"));

		sprites::SpriteAnimator* animator = static_cast<sprites::SpriteAnimator*>(cm->createComponent("SpriteAnimator"));
		animator->setSpriteSheet("wizard");
		go->addComponent(animator);

		go->getTransform().setIgnoreParent(false);
		go->getTransform().setParent(&g->getTransform());

		go->getTransform().place(0, 0, 0);
		go->getTransform().rotateAbsolute(glm::vec3(45, 0, 0));
		go->getTransform().scaleAbsolute(10, 10, 10);*/
	}
}
