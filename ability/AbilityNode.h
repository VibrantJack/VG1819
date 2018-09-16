#pragma once
#include <string>
#include <map>
#include <vector>
//Rock

class Unit;

class AbilityNode
{
public:
	AbilityNode() {};
	~AbilityNode() {};

	virtual int effect() { return -1; };
	virtual int effect(Unit* p_target, int p_value) { return -1; };
	virtual int effect(Unit* p_target, const std::string &p_name, int p_value) { return -1; };
	//the method call
	//TO DO: override method with parameters
};

