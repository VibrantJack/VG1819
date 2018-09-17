#include "AbilityNode.h"



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

int AbilityNode::effect(Unit* p_target, int p_value) 
{ 
	return -1;
};

int AbilityNode::effect(Unit* p_target, const std::string &p_name, int p_value) 
{ 
	return -1; 
};