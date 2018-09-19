#pragma once
#include "CheckHPNode.h"
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
		//TO DO: implement destroy method for unit
		//else if (p_target->m_HP <= 0)
		//p_target->destroyedByDamage();
		return 0;
	}

}
