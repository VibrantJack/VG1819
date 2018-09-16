#pragma once
#include "AbilityNode.h"

class ChangeHPNode : public AbilityNode
{
public:
	ChangeHPNode() :AbilityNode() {};

	int effect(Unit* p_target, int p_value);
};