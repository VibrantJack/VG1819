#pragma once
#include "unit/UnitCommon.h"
#include "unit/unitComponent/StatusContainer.h"
#include "ability/StatusManager.h"
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

		//kitten::K_GameObject* spawnUnitObject(Unit* p_unitData);

		kitten::K_GameObject* spawnUnitObject(const int& p_unitIdentifier);
	private:

		static UnitSpawn * m_instance;

		kitten::K_GameObject* m_textBoxGO;

		//std::vector<unit::AbilityDescription> readAD();
		//ability::Status* readSD(unit::StatusDescription* p_sd);

		//Unit* spawnUnitFromData(UnitData* p_unitData);
		//void spawnCommander(Unit* p_u, UnitData* p_unitData);

		kitten::K_Component* createClickableBox(UnitSize p_size);
	};
}
