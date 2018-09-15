#pragma once

#include "AbilityNode.h"

#include <string>
#include <map>
#include <vector>

//Rock

class Ability
{
public:
	std::map<std::string, int> m_counter;
	//counter can be CD, CT or maybe how many times can be used(even it does not apply for now)
	//so I choose counter which is map which is more flexible
	//<name of the counter, value of the counter>

	std::string m_name;
	std::string m_description;//the text that will be showed to player

	std::vector<AbilityNode> m_abilityNodes;//the list of nodes that will affect

	//TO DO: Range Component

	Ability();
	~Ability();

	virtual int effect() = 0;
	//Should go through every nodes and send proper parameters
};

