#pragma once
#include "UnitData.h"
#include "UnitMonitor.h"
#include "UnitSpawn.h"

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