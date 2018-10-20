#pragma once
#include "unit/UnitCommon.h"
#include "unit/Unit.h"
#include "unit/InitiativeTracker/UnitTurn.h"

//Rock
//This class should be singleton
//it handles all units on the board
//it decides the order the units take turn

namespace unit
{
	class UnitTurn;
	class InitiativeTracker
	{
		friend class InitiativeTrackerUI;
	private:
		static InitiativeTracker * sm_instance;
		UnitTurn* m_uturn;
		InitiativeTrackerUI* m_UI;

		std::vector<kitten::K_GameObject*> m_unitObjectList;
		int m_currentUnitIndex;

		void sortListByIn();
	public:
		InitiativeTracker();
		~InitiativeTracker();

		static void createInstance();
		static void destroyInstance();
		static InitiativeTracker* getInstance();

		void addUnit(kitten::K_GameObject* p_unit);
		bool removeUnit(kitten::K_GameObject* p_unit);

		//TO DO: by ID or name or something
		kitten::K_GameObject* getCurrentUnit();
		std::vector<kitten::K_GameObject*> getUnitList();

		//turn phase
		//start of whole turn->unit turn->next->repeat until no more unit->start of whole turn
		void gameTurnStart();
		void unitTurnEnd();
		void gameTurnEnd();
	};
}