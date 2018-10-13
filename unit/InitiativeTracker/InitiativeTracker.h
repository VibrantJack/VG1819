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
		std::vector<kitten::K_GameObject*>::iterator m_currentUnitIterator;

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
		kitten::K_GameObject* findUnit();
		std::vector<kitten::K_GameObject*> getList();

		void gameTurnStart();
		void unitTurnEnd();
	};
}