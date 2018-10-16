#include "UnitTest.h"
#include "ability/node/AbilityNodeManager.h"
#include <iostream>
#include "kibble/kibble.hpp"
#include "_Project\PrintWhenClicked.h"
#include "_Project\UseAbilityWhenClicked.h"
#include "components\PowerTracker.h"
#include "kitten\K_ComponentManager.h"
//Rock
//test the unit data

namespace unit
{
	UnitTest* UnitTest::m_instance = nullptr;

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
		//createInstance
		ability::StatusManager::createInstance();
		ability::AbilityManager::createInstance();
		ability::AbilityNodeManager::createInstance();

		std::string name = "testDummy";
		int HP = 3;
		int MV = 3;
		int IN = 3;
		int Cost = 3;
		UnitSize size = point;

		std::vector<std::string> tags;
		tags.push_back("Dummy");
		tags.push_back("Neutral");

		std::vector<std::string> abilityDescription;
		abilityDescription.push_back("Heal");
		std::vector<std::string> statusDescription;

		//UnitData* data = new UnitData(name, HP, MV, IN, Cost, size, tags, abilityDescription, statusDescription);

		kibble::UnitDataParser* parser = kibble::getUnitDataParserInstance();
		kitten::K_GameObject* random = UnitSpawn::getInstance()->spawnUnitObject(parser->getUnit("testDummy.txt"));
		random->getTransform().move(1.5f, -1.0f, 1.0f);

		// Testing selecting spawned unit
		kitten::K_ComponentManager* compMan = kitten::K_ComponentManager::getInstance();

		kitten::K_Component* clickBox = compMan->createComponent("ClickableBoxUnitTest");
		random->addComponent(clickBox);

		PrintWhenClicked* printWhenClick = static_cast<PrintWhenClicked*>(compMan->createComponent("PrintWhenClicked"));
		printWhenClick->setMessage("Unit clicked");
		random->addComponent(printWhenClick);

		//UseAbilityWhenClicked* useAbility = new UseAbilityWhenClicked();
		//random->addComponent(useAbility);
		//useAbility->start();
		kitten::K_Component* useAbiltyWhenClicked = compMan->createComponent("UseAbilityWhenClicked");
		random->addComponent(useAbiltyWhenClicked);

		kitten::K_Component* selectAbility = compMan->createComponent("SelectAbility");
		random->addComponent(selectAbility);
		// End testing selecting spawned unit

		// Moved this component to attach the the parent GO of a tile GO
		// Testing PowerTracker component
		//kitten::K_Component* powerTracker = compMan->createComponent("PowerTracker");
		//random->addComponent(powerTracker);
		// End testing PowerTracker component

		//kitten::K_GameObject* random = UnitSpawn::getInstance()->spawnUnitObject(parser->getUnit("Priest.txt"));

		unit::Unit* u = random->getComponent<unit::Unit>();
		UnitMonitor::getInstanceSafe()->printUnit(u);
		//kitten::K_GameObject* dummy = UnitSpawn::getInstanceSafe()->spawnUnitFromData(data);
		//kitten::K_GameObject* dummyC = UnitSpawn::getInstance()->spawnCommanderFromData(data);

		/*
		dummy->m_attributes["HP"] = 0;
		std::cout << "Dummy with 0 HP" << std::endl;
		std::cout << std::endl;
		UnitMonitor::getInstanceSafe()->printUnit(dummy);

		dummy->useAbility(0);

		std::cout << std::endl;
		std::cout << "Dummy used heal (+4HP) on itself." << std::endl;
		UnitMonitor::getInstance()->printUnit(dummy);

		std::cout << std::endl;
		std::cout << "Dummy create from kibble." << std::endl;
		UnitMonitor::getInstance()->printUnit(random);
		*/
	}
}

