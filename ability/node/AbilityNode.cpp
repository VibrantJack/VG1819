#include "AbilityNode.h"

//Rock

namespace ability
{

	AbilityNode::AbilityNode()
	{
	};

	AbilityNode::~AbilityNode()
	{
	}

	int AbilityNode::effect()
	{
		return -1;
	};

	int AbilityNode::effect(unit::Unit* p_target, int p_value)
	{
		return -1;
	};

	int AbilityNode::effect(unit::Unit* p_target, const std::string &p_name, int p_value)
	{
		return -1;
	};
}
