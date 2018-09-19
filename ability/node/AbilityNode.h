#pragma once
#include <string>
#include <map>
#include <vector>
//Rock

namespace unit
{
	class Unit;
}

namespace ability
{
	class AbilityNode
	{
	public:
		AbilityNode();
		~AbilityNode();

		std::string m_name;

		virtual int effect();
		virtual int effect(unit::Unit* p_target, int p_value);
		virtual int effect(unit::Unit* p_target, const std::string &p_name, int p_value);
		//the method call
		//TO DO: override method with parameters
	};
}


