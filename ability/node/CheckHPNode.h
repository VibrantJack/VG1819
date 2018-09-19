#pragma once
#include "AbilityNode.h"

//Rock

namespace ability
{
	class CheckHPNode : public ability::AbilityNode
	{
	public:
		CheckHPNode();

		int effect(unit::Unit* p_target);
	};
}
