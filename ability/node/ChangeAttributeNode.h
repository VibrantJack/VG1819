#pragma once
#include "AbilityNode.h"

//Rock

namespace ability
{
	class ChangeAttributeNode : public ability::AbilityNode
	{
	public:
		ChangeAttributeNode();

		int effect(unit::Unit* p_target, const std::string &p_name, int p_value);
	};
}

