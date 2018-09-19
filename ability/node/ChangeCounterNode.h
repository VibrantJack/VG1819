#pragma once
#include "AbilityNode.h"

class ChangeCounterNode : public AbilityNode
{
public:
	ChangeCounterNode();

	int effect(Unit* p_target, const std::string &p_name, int p_value);
};
