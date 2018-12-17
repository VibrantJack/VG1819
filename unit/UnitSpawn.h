#pragma once
#include "unit/UnitCommon.h"
#include "unit/unitComponent/StatusContainer.h"
#include "ability/StatusManager.h"
#include "unitComponent/unitAction/ActionButtonStore.h"

//Rock

namespace unit
{
	class UnitSpawn
	{
	public:
		enum UnitIndex
		{
			testDummy = 0,
			Priest,
			Archer,
			Duelist, 
			Engineer,
			Wall,
			newUnitObject,
			Pyromancer,
			StoneSlinger,
			ArrowTower,
			Armory,
			DivineStatue,
			Oligarch,
			King,
			Queen
		};

		UnitSpawn();
		~UnitSpawn();

		static UnitSpawn* getInstance();
		static UnitSpawn* getInstanceSafe();

		//kitten::K_GameObject* spawnUnitObject(Unit* p_unitData);

		kitten::K_GameObject* spawnUnitObject(const int& p_unitIdentifier);
	private:

		static UnitSpawn * m_instance;

		ActionButtonStore* m_storage;

		//std::vector<unit::AbilityDescription> readAD();
		//ability::Status* readSD(unit::StatusDescription* p_sd);

		//Unit* spawnUnitFromData(UnitData* p_unitData);
		//void spawnCommander(Unit* p_u, UnitData* p_unitData);

		kitten::K_Component* createClickableBox(UnitSize p_size);
	};
}
