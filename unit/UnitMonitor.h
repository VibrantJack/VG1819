#pragma once
#include "Unit.h"

//Rock
//this class output information about a unit
//used for test purpose

namespace unit
{
	class UnitMonitor
	{
	private:
		static UnitMonitor * m_instance;
		void printStatus(unit::StatusContainer* p_s);
	public:
		UnitMonitor();
		~UnitMonitor();

		static UnitMonitor* getInstance();
		static UnitMonitor* getInstanceSafe();

		void printUnit(Unit* p_u);
	};
}
