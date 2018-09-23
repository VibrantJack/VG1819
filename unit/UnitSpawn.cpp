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

		unit->m_attributes["MaxHP"] = hp;
		unit->m_attributes["HP"] = hp;
		unit->m_attributes["baseIN"] = in;
		unit->m_attributes["IN"] = in;
		unit->m_attributes["baseMV"] = mv;
		unit->m_attributes["MV"] = mv;
		unit->m_attributes["baseCost"] = cost;
		unit->m_attributes["Cost"] = cost;
		//set lv to 1
		unit->m_attributes["LV"] = 1;

		unit->m_size = p_unitData->m_size;

		//TO DO readAD

		//TO DO readSD

		return unit;
	}

	unit::Commander * UnitSpawn::spawnCommanderFromData(UnitData * p_unitData)
	{
		unit::Commander* commander = static_cast<Commander*>(spawnUnitFromData(p_unitData));

		//change lv to -1 since it doesn't apply to commander
		//unit->m_LV = -1;
		commander->m_attributes["LV"] = -1;

		commander->m_ID = "testCommander01";

		commander->m_porPath = p_unitData->m_porPath;

		return commander;
	}
}
