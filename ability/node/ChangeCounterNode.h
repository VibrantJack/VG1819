#pragma once
#include "AbilityNode.h"

//Rock

namespace ability
{
	class ChangeCounterNode : public ability::AbilityNode
	{
	public:
		ChangeCounterNode();

		int effect(unit::Unit* p_target, const std::string &p_name, int p_value);
	};
}

