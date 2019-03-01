#pragma once
#include "unit/Unit.h"

//Rock
//this class output information about a unit
//used for test purpose

namespace unit
{
	class UnitMonitor
	{
	private:
		static UnitMonitor * m_instance;
	public:
		UnitMonitor();
		~UnitMonitor();

		static UnitMonitor* getInstance();
		static UnitMonitor* getInstanceSafe();
		static void destroyInstance();

		void printUnit(Unit* p_u);
		void printStatus(unit::StatusContainer* p_s);
		void printIT();
	};
}
