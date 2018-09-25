#pragma once
#include "ability/node/AbilityNode.h"
#include "ability/AbilityInfoPackage.h"

//Rock

namespace ability
{
	ChangeAbilityInfoNode::ChangeAbilityInfoNode()
	{
	}

	int ChangeAbilityInfoNode::effect(ability::AbilityInfoPackage* p_pack, const std::string& p_valueName, int p_value)
	{
		p_pack->m_intValue[p_valueName] += p_value;
		return 0;
	}

}