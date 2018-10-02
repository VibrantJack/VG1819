#pragma once
#include "UnitSpawn.h"
#include "unit/Commander.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten/K_ComponentManager.h"
//Rock

namespace unit
{
	UnitSpawn* UnitSpawn::m_instance = nullptr;

	UnitSpawn::UnitSpawn()
	{
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
		Unit* unit = nullptr;
		Commander* commander = nullptr;

		if (p_unitData->m_tags[0] == "Commander")
		{
			commander = spawnCommanderFromData(p_unitData);
		}
		else
		{
			unit = spawnUnitFromData(p_unitData);
		}

		//unit graphic
		kitten::K_Component* unitG = kitten::K_ComponentManager::getInstance()->createComponent("UnitGraphic");

		//unit object
		kitten::K_GameObject* unitObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		if (commander == nullptr)
			unitObject->addComponent(unit);
		else
			unitObject->addComponent(commander);
		unitObject->addComponent(unitG);

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
			unit->m_ADList[it->m_stringValue["name"]] = it;
		}

		//readSD
		for (auto it : p_unitData->m_sd)
		{
			readSD(it)->attach(unit);
		}

		return unit;
	}

	unit::Commander * UnitSpawn::spawnCommanderFromData(UnitData * p_unitData)
	{
		unit::Commander* commander = static_cast<Commander*>(spawnUnitFromData(p_unitData));

		//change lv to -1 since it doesn't apply to commander
		//unit->m_LV = -1;
		commander->m_attributes["lv"] = -1;

		commander->m_ID = "testCommander01";

		commander->m_porPath = p_unitData->m_porPath;

		return commander;
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
