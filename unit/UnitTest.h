#pragma once
#include "UnitMonitor.h"
#include "UnitSpawn.h"
#include "UnitCommon.h"

//Rock

namespace unit
{
	class UnitTest
	{
	private:
		static UnitTest * m_instance;
		static bool m_bTested;
	public:
		UnitTest();
		~UnitTest(){}

		static UnitTest* getInstance();
		static UnitTest* getInstanceSafe();
		static void destroyInstance();

		void test();

		static bool isTested() { return m_bTested; }
	};
}