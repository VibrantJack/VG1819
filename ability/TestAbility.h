#pragma once
#include "Ability.h"
#include "ChangeHpNode.h"
#include "ChangeCounterNode.h"

class TestAbility : public Ability
{
public:
	TestAbility(Unit* p_u);
	~TestAbility();
	int effect();
};