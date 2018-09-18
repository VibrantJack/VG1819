#include "ChangeCounterNode.h"
#include "Unit/Unit.h"

ChangeCounterNode::ChangeCounterNode()
{
}

int ChangeCounterNode::effect(Unit * p_target, const std::string & p_name, int p_value)
{
	std::map<std::string, int>::iterator it;

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

	if (p_target->m_attributes[p_name] < 0)
		p_target->m_attributes[p_name];//no negative counter

	return 0;
}
