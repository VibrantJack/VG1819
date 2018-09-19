#pragma once
#include "Unit.h"
#include "UnitData.h"

//Rock

namespace unit
{
	class UnitSpawn
	{
	private:
		static UnitSpawn * m_instance;
	public:
		UnitSpawn();
		~UnitSpawn();

		static UnitSpawn* getInstance();
		static UnitSpawn* getInstanceSafe();

		Unit* spawnUnitFromData(UnitData* p_unitData);
		Unit* spawnCommanderFromData(UnitData* p_unitData);

		//TO DO: Spawn unit by ability, it may not be same as spawn unit from data
		//it should take some parameters that indicate what to change
		Unit* spawnUnitFromAbility(UnitData* p_unitData);
	};

}
