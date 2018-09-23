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
		virtual int effect(unit::Unit* p_target);
		virtual int effect(unit::Unit* p_target, int p_value);
		virtual int effect(unit::Unit* p_target, const std::string &p_name, int p_value);
		//the method call
		//TO DO: override method with parameters
	};

	class ChangeAttributeNode : public ability::AbilityNode
	{
	public:
		ChangeAttributeNode();

		int effect(unit::Unit* p_target, const std::string &p_name, int p_value);
	};

	class CheckHPNode : public ability::AbilityNode
	{
	public:
		CheckHPNode();

		int effect(unit::Unit* p_target);
	};

	//TO DO: implement
	class CreateUnitNode : public ability::AbilityNode
	{
	public:
		CreateUnitNode();

		int effect(unit::Unit* p_target);
	};
}


