#pragma once
#include "ability/node/AbilityNode.h"
#include "Unit/Unit.h"

//Rock

namespace ability
{
	ChangeAbilityDescriptionNode::ChangeAbilityDescriptionNode()
	{
	}

	int ChangeAbilityDescriptionNode::effect(unit::Unit* p_target, const std::string& p_abilityName, const std::string& p_valueName, int p_value)
	{
		//find ability
		for (unit::AbilityDescription* ad : p_target->m_abilityDescription)
		{
			if (ad->m_stringValue["name"] == p_abilityName)
			{
				ad->m_stringValue[p_valueName] += p_value;
				return 0;
			}
		}

		//not found ability
		return 1;
	}

}