#pragma once
#include "unit/InitiativeTracker/UnitTurn.h"
#include "kitten/K_GameObject.h"
#include "unit/InitiativeTracker/UnitAura.h"
//Rock
//This class should be singleton
//it handles all units on the board
//it decides the order the units take turn

namespace unit
{
	class UnitTurn;
	class InitiativeTrackerUI;
	class InitiativeTracker
	{
	private:
		static InitiativeTracker * sm_instance;
		UnitTurn* m_uturn;
		InitiativeTrackerUI* m_UI;
		kitten::K_GameObject* m_uAura;

		//list for new units
		std::vector<kitten::K_GameObject*> m_waitUnitObjectList;
		//list for old units
		std::vector<kitten::K_GameObject*> m_unitObjectList;

		int m_currentUnitIndex;

		void sortListByIn(int p_list=0);
		void addWaitList();
		int getUnitObjectIndex(kitten::K_GameObject* p_uGO);
	public:
		InitiativeTracker();
		~InitiativeTracker();

		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new InitiativeTracker(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static InitiativeTracker* getInstance() { return sm_instance; };

		void addUnit(kitten::K_GameObject* p_unit);
		bool removeUnit(kitten::K_GameObject* p_unit);

		kitten::K_GameObject* getUnitByIndex(int p_index);
		int getUnitNumber();
		kitten::K_GameObject* getCurrentUnit();
		int getCurrentUnitIndex();

		std::vector<kitten::K_GameObject*> getUnitList();

		//turn phase
		//start of whole turn->unit turn->next->repeat until no more unit->start of whole turn
		void gameTurnStart();
		void unitTurnEnd();
		void gameTurnEnd();
	};
}