#pragma once

//Rock

class AbilityNode
{
public:
	AbilityNode();
	~AbilityNode();

	virtual int effect() = 0;
	//the method call
	//TO DO: override method with parameters
};

