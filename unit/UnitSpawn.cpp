#pragma once
#include "UnitSpawn.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten/K_ComponentManager.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"
#include "unit/unitComponent/UnitClickable.h"
#include "unit/unitComponent/UnitMove.h"
//board clickable
#include "board/clickable/PrintWhenClicked.h"

#include "puppy/Text/TextBox.h"

//Rock

namespace unit
{
	UnitSpawn* UnitSpawn::m_instance = nullptr;

	UnitSpawn::UnitSpawn()
	{
		puppy::TextBox* textBox = static_cast<puppy::TextBox*>(kitten::K_ComponentManager::getInstance()->createComponent("TextBoxAbilities"));
		textBox->setColor(1, 1, 1);
		textBox->setText("");

		kitten::K_Component* select = kitten::K_ComponentManager::getInstance()->createComponent("SelectAbility");

		m_textBoxGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		m_textBoxGO->addComponent(textBox);
		m_textBoxGO->getTransform().place2D(1000, 600);

		m_textBoxGO->addComponent(select);
	}

	UnitSpawn::~UnitSpawn()
	{
	}

	UnitSpawn * UnitSpawn::getInstance()
	{
		return m_instance;
	}

	UnitSpawn * UnitSpawn::getInstanceSafe()
	{
		if (m_instance == nullptr)
			m_instance = new UnitSpawn();
		return m_instance;
	}

	kitten::K_GameObject * UnitSpawn::spawnUnitObject(UnitData * p_unitData)
	{
		//create unit 
		Unit* unit = nullptr;
		Commander* commander = nullptr;
		//check every tag
		for (int i = 0; i < p_unitData->m_tags.size(); i++)
		{
			if (p_unitData->m_tags[i] == "Commander")
			{
				commander = spawnCommanderFromData(p_unitData);
				break;
			}
		}
		if (commander == nullptr)
		{	
			unit = spawnUnitFromData(p_unitData);
		}

		//get component manager
		kitten::K_ComponentManager* cm = kitten::K_ComponentManager::getInstance();

		//create unit graphic
		UnitGraphic* unitG = static_cast<UnitGraphic*>(cm->createComponent("UnitGraphic"));
		unitG->setTexture(p_unitData->m_texPath.c_str());

		//create unit move
		kitten::K_Component* uMove = cm->createComponent("UnitMove");

		//create click box
		kitten::K_Component* uBox = createClickableBox(p_unitData->m_size);

		//create clickable
		unit::UnitClickable* uClick = static_cast<unit::UnitClickable*>(cm->createComponent("UnitClickable"));
		uClick->setTextBox(m_textBoxGO);

		//unit object
		kitten::K_GameObject* unitObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		if (commander == nullptr)
			unitObject->addComponent(unit);
		else {
			unitObject->addComponent(commander);

			//PrintWhenClicked* printWhenClick = static_cast<PrintWhenClicked*>(cm->createComponent("PrintWhenClicked"));
			//printWhenClick->setMessage("Unit clicked");
			//unitObject->addComponent(printWhenClick);

			//kitten::K_Component* useAbility = cm->createComponent("UseAbilityWhenClicked");
			//unitObject->addComponent(useAbility);

		}

		//attach component
		unitObject->addComponent(unitG);
		unitObject->addComponent(uMove);
		unitObject->addComponent(uBox);
		unitObject->addComponent(uClick);

		//rotate to face camera
		unitObject->getTransform().rotateRelative(glm::vec3(45, 0, 0));

		//add object to Initiative Tracker
		unit::InitiativeTracker::getInstance()->addUnit(unitObject);

		return unitObject;
	}

	unit::Unit * UnitSpawn::spawnUnitFromData(UnitData * p_unitData)
	{
		Unit* unit = new Unit();

		//TO DO: an ID system instead of random words
		unit->m_ID = "testUnit01";//hard coded for now

		//copy tag, name and attributes
		unit->m_tags = p_unitData->m_tags;
		unit->m_name = p_unitData->m_name;

		int hp = p_unitData->m_HP;
		int in = p_unitData->m_IN;
		int mv = p_unitData->m_MV;
		int cost = p_unitData->m_Cost;

		unit->m_attributes["max_hp"] = hp;
		unit->m_attributes["hp"] = hp;
		unit->m_attributes["base_in"] = in;
		unit->m_attributes["in"] = in;
		unit->m_attributes["base_mv"] = mv;
		unit->m_attributes["mv"] = mv;
		unit->m_attributes["base_cost"] = cost;
		unit->m_attributes["cost"] = cost;
		//set lv to 1
		unit->m_attributes["lv"] = 1;

		unit->m_size = p_unitData->m_size;

		//readAD
		for (auto it : p_unitData->m_ad)
		{
			//get copy
			AbilityDescription * ad = new AbilityDescription();
			ad->m_intValue = it->m_intValue;
			ad->m_stringValue = it->m_stringValue;
			unit->m_ADList[it->m_stringValue["name"]] = ad;
		}

		//readSD
		for (auto it : p_unitData->m_sd)
		{
			unit->addStatus(readSD(it));
		}

		// Set unit's clientId to -1, meaning no player owns this unit yet
		// Unit clientId gets set in ClientGame::summonUnit()
		unit->m_clientId = -1;

		return unit;
	}

	unit::Commander * UnitSpawn::spawnCommanderFromData(UnitData * p_unitData)
	{
		unit::Commander* commander = static_cast<Commander*>(spawnUnitFromData(p_unitData));
		commander->init();
		//change lv to -1 since it doesn't apply to commander
		//unit->m_LV = -1;
		commander->m_attributes["lv"] = -1;

		commander->m_ID = "testCommander01";

		// Had to comment this out for testing Commander's ManipulateTile ability, using testDummy.txt
		// Threw errors every other time
		//commander->m_porPath = p_unitData->m_porPath;

		return commander;
	}

	kitten::K_Component * UnitSpawn::createClickableBox(UnitSize p_size)
	{
		switch (p_size)
		{
		case unit::point:
			return kitten::K_ComponentManager::getInstance()->createComponent("ClickableBoxForPointUnit");
			break;
		case unit::cube:
			return kitten::K_ComponentManager::getInstance()->createComponent("ClickableBoxForCubeUnit");
			break;
		default:
			return nullptr;
		}
		return nullptr;
	}

	ability::Status* UnitSpawn::readSD(unit::StatusDescription* p_sd)
	{
		std::string name = p_sd->m_stringValue["name"];

		//find a empty copy of the status
		ability::Status* s = ability::StatusManager::getInstance()->findStatus(name);

		if (p_sd->m_stringValue.find("description") != p_sd->m_stringValue.end())
		{
			s->m_description = p_sd->m_stringValue["description"];
		}
		
		s->m_TPList.insert(s->m_TPList.end(),p_sd->m_TPList.begin(),p_sd->m_TPList.end());

		//for lv status
		if (p_sd->m_intValue.find("lv") != p_sd->m_intValue.end())
		{
			s->m_LV = p_sd->m_intValue["lv"];
			//hp
			if (p_sd->m_intValue.find("hp") != p_sd->m_intValue.end())
			{
				int hp = p_sd->m_intValue["hp"];
				s->m_attributeChange["hp"] = hp;
				s->m_attributeChange["max_hp"] = p_sd->m_intValue["hp"];
			}
			//in
			if (p_sd->m_intValue.find("in") != p_sd->m_intValue.end())
			{
				s->m_attributeChange["in"] = p_sd->m_intValue["in"];
				s->m_attributeChange["base_in"] = p_sd->m_intValue["in"];
			}
			//mv
			if (p_sd->m_intValue.find("mv") != p_sd->m_intValue.end())
			{
				s->m_attributeChange["mv"] = p_sd->m_intValue["mv"];
				s->m_attributeChange["base_mv"] = p_sd->m_intValue["mv"];
			}
		}

		return s;
	}
}
