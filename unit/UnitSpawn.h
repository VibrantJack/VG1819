#pragma once
#include "unit/UnitData.h"
#include "unit/Commander.h"

//Rock

//I think this class can be merged to kibble unit data parser
//then we don't need unit data as a middle point
namespace unit
{
	class UnitSpawn
	{
	public:
		UnitSpawn();
		~UnitSpawn();

		static UnitSpawn* getInstance();
		static UnitSpawn* getInstanceSafe();

		kitten::K_GameObject* spawnUnitObject(UnitData* p_unitData);
	private:

		static UnitSpawn * m_instance;
		std::vector<unit::AbilityDescription> readAD();
		unit::StatusContainer* readSD();

		unit::Unit* spawnUnitFromData(UnitData* p_unitData);
		unit::Commander* spawnCommanderFromData(UnitData* p_unitData);

		//TO DO: Spawn unit by ability, it may not be same as spawn unit from data
		//it should take some parameters that indicate what to change
		unit::Unit* spawnUnitFromAbility(UnitData* p_unitData);

	};
}
