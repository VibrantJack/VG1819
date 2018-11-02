#pragma once
#include "ability/node/AbilityNode.h"
#include "Unit/Unit.h"

//Rock

namespace ability
{
	CheckHPNode::CheckHPNode()
	{
	}

	int CheckHPNode::effect(unit::Unit* p_target)
	{
		if (p_target->m_attributes["hp"] > p_target->m_attributes["max_hp"])
			p_target->m_attributes["hp"] = p_target->m_attributes["max_hp"];
		else if (p_target->m_attributes["hp"] <= 0)
			p_target->destroyedByDamage();
		return 0;
	}

}
