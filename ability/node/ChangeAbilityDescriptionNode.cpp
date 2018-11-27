#pragma once
#include "ability/node/AbilityNode.h"
#include "Unit/Unit.h"
#include <iostream>
//Rock

namespace ability
{
	ChangeAbilityDescriptionNode::ChangeAbilityDescriptionNode()
	{
	}

	int ChangeAbilityDescriptionNode::effect(unit::Unit* p_target, const std::string& p_abilityName, const std::string& p_valueName, int p_value)
	{
		//find ability
		if (p_target->m_ADList.find(p_abilityName) != p_target->m_ADList.end())
		{
			std::cout << p_abilityName << " : " << p_valueName << " is changed by " << p_value << std::endl;
			p_target->m_ADList[p_abilityName]->m_intValue[p_valueName] += p_value;
			return 0;
		}
		//not found ability
		return 1;
	}

	int ChangeAbilityDescriptionNode::effect(unit::Unit* p_target, const std::string& p_abilityName, const std::string& p_valueName, const std::string& p_value)
	{
		//find ability
		if (p_target->m_ADList.find(p_abilityName) != p_target->m_ADList.end())
		{
			std::cout << p_abilityName << " : " << p_valueName << " is changed to " << p_value << std::endl;
			p_target->m_ADList[p_abilityName]->m_stringValue[p_valueName] = p_value;
			return 0;
		}
		//not found ability
		return 1;
	}

}