#include "ChangeCounterNode.h"
#include "Unit/Unit.h"

ChangeCounterNode::ChangeCounterNode()
{
}

int ChangeCounterNode::effect(Unit * p_target, const std::string & p_name, int p_value)
{
	std::map<std::string, int>::iterator it;

	it = p_target->m_Counter.find(p_name);
	if (it != p_target->m_Counter.end())
		it->second += p_value;
	else
	{
		p_target->m_Counter[p_name] = p_value;
	}

	return 0;
}
