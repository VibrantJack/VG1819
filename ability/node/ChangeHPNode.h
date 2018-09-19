#pragma once
#include "AbilityNode.h"

//Rock

namespace ability
{
	class ChangeHPNode : public ability::AbilityNode
	{
	public:
		ChangeHPNode();

		int effect(unit::Unit* p_target, int p_value);
	};
}
