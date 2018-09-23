#pragma once
#include "UnitData.h"
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
	public:
		UnitTest();
		~UnitTest();

		static UnitTest* getInstance();
		static UnitTest* getInstanceSafe();

		void test();
	};
}