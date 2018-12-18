#pragma once
#include "ability/node/AbilityNode.h"
#include "Unit/Unit.h"
#include "kitten/sprites/SpriteGroup.h"
//Rock

namespace ability
{
	CheckHPNode::CheckHPNode()
	{
	}

	int CheckHPNode::effect(unit::Unit* p_target)
	{
		if (p_target->m_attributes[UNIT_HP] > p_target->m_attributes[UNIT_MAX_HP])
			p_target->m_attributes[UNIT_HP] = p_target->m_attributes[UNIT_MAX_HP];
		else if (p_target->m_attributes[UNIT_HP] <= 0)
			p_target->destroyedByDamage();

		int hp = p_target->m_attributes[UNIT_HP];
		int max = p_target->m_attributes[UNIT_MAX_HP];

		p_target->getGameObject().getComponent<sprites::SpriteGroup>()->checkHP(hp,max);

		return 0;
	}

}
