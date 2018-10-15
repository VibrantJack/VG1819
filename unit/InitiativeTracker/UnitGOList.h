#pragma once
#include "unit/UnitCommon.h"
#include "unit/Unit.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"

//Rock
//This class is part of Initiative Tracker
//it contains a list of all units on the board
//it handles how to manage the information

namespace unit
{
	class UnitGOList
	{
	private:
		std::vector<kitten::K_GameObject*> m_unitObjectList;
		std::vector<kitten::K_GameObject*>::iterator m_currentUnitIterator;

		void sortListByIn();
	public:
		UnitGOList();
		~UnitGOList();

		void addUnit(kitten::K_GameObject* p_unit);
		bool removeUnit(kitten::K_GameObject* p_unit);

		std::vector<kitten::K_GameObject*>::iterator getCurrentUnitIterator();
		std::vector<kitten::K_GameObject*> getList();
	};
}
