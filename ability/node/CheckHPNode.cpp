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
		if (p_target->m_attributes["HP"] > p_target->m_attributes["MaxHP"])
			p_target->m_attributes["HP"] = p_target->m_attributes["MaxHP"];
		else if (p_target->m_attributes["HP"] <= 0)
			p_target->destroyedByDamage();
		return 0;
	}

}
