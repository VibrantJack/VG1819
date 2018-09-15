#pragma once
#include "Unit.h"

class UnitMonitor
{
private:
	static UnitMonitor * m_instance;
	void printAbility(Ability* p_a);
	void printStatus(Status* p_s);
public:
	UnitMonitor();
	~UnitMonitor();

	static UnitMonitor* getInstance();
	static UnitMonitor* getInstanceSafe();

	void printUnit(Unit* p_u);
};

