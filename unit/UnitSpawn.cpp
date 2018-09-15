#include "UnitSpawn.h"

//Rock

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

	//copy tag, and attributes
	unit->m_tags = * p_unitData->getTags();
	unit->m_name = p_unitData->getName();
	unit->m_HP = p_unitData->getHP();
	unit->m_IN = p_unitData->getIN();
	unit->m_MV = p_unitData->getMV();
	unit->m_Cost = p_unitData->getCost();
	unit->m_size = p_unitData->getSize();

	//set lv to 1
	unit->m_LV = 1;

	//find each ability and status from library and attach to this unit
	for (std::string abilityName : * p_unitData->getAbility())
	{
		//TO DO: newability = find(abilityName)
		//unit->addAbility(Ability)
	}
	for (std::string statusName : *p_unitData->getStatus())
	{
		//TO DO: newstatus = find(statusName)
		//unit->addStatus(status)
	}

	return unit;
}

Unit * UnitSpawn::spawnCommanderFromData(UnitData * p_unitData)
{
	Unit* unit = spawnUnitFromData(p_unitData);

	//change lv to -1 since it doesn't apply to commander
	unit->m_LV = -1;

	unit->m_ID = "testCommander01";

	return unit;
}
