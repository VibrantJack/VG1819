#include "UnitSpawn.h"
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

	Unit * UnitSpawn::spawnUnitFromData(UnitData * p_unitData)
	{
		Unit* unit = new Unit();

		//TO DO: an ID system instead of random words
		unit->m_ID = "testUnit01";//hard coded for now

								  //copy tag, name and attributes
		unit->m_tags = *p_unitData->getTags();
		unit->m_name = p_unitData->getName();

		int hp = p_unitData->getHP();
		int in = p_unitData->getIN();
		int mv = p_unitData->getMV();
		int cost = p_unitData->getCost();

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

		/*unit->m_MaxHP = hp;
		unit->m_HP = hp;
		unit->m_baseIN = in
		unit->m_IN = in;
		unit->m_baseMV = mv;
		unit->m_MV = mv;
		unit->m_baseCost = cost;
		unit->m_Cost = cost;
		unit->m_LV = 1*/

		unit->m_size = p_unitData->getSize();

		unit->m_Ability = *p_unitData->getAbility();

		//TO DO add status

		return unit;
	}

	Unit * UnitSpawn::spawnCommanderFromData(UnitData * p_unitData)
	{
		Unit* unit = spawnUnitFromData(p_unitData);

		//change lv to -1 since it doesn't apply to commander
		//unit->m_LV = -1;
		unit->m_attributes["LV"] = -1;

		unit->m_ID = "testCommander01";

		return unit;
	}

}
