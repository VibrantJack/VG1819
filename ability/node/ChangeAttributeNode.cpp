#pragma once
#include "ability/node/AbilityNode.h"
#include "Unit/Unit.h"
#include <iostream>
//Rock

namespace ability
{

	ChangeAttributeNode::ChangeAttributeNode()
	{
	}

	int ChangeAttributeNode::effect(unit::Unit* p_target, const std::string & p_name, int p_value)
	{
		std::unordered_map<std::string, int>::iterator it;

		std::cout << p_target->m_name << " : "<<p_name<<" is changed by " << p_value << std::endl;

		it = p_target->m_attributes.find(p_name);
		if (it != p_target->m_attributes.end())
		{
			it->second += p_value;
		}
		else
		{
			//if counter doesn't exist, add it
			p_target->m_attributes[p_name] = p_value;
		}

		if (p_name == UNIT_HP || p_name == UNIT_MAX_HP)
		{
			AbilityNodeManager::getInstance()->findNode(CheckHP)->effect();
		}

		if (p_target->m_attributes[p_name] < 0)
			p_target->m_attributes[p_name];//no negative value

		return 0;
	}

}