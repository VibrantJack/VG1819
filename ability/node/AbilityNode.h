#pragma once
#include "ability/AbilityInfoPackage.h"
#include <string>
#include <map>
#include <vector>
//Rock

namespace unit
{
	class Unit;
	struct UnitData;
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
		virtual int effect(unit::Unit* p_target, const std::string& p_abilityName, const std::string& p_valueName, int p_value);
		virtual int effect(ability::AbilityInfoPackage* p_pack, const std::string& p_valueName, int p_value);
		virtual int effect(unit::UnitData* p_data);
		//the method call
		//TO DO: override method with parameters
	};

	class ChangeAttributeNode : public ability::AbilityNode
	{
		//this node changes a unit's attribute
	public:
		ChangeAttributeNode();

		int effect(unit::Unit* p_target, const std::string &p_name, int p_value);
	};

	class CheckHPNode : public ability::AbilityNode
	{
		//this node check unit's hp
		//if hp > maxhp, change to max hp
		//if hp <= 0, destroy the unit
	public:
		CheckHPNode();

		int effect(unit::Unit* p_target);
	};

	class ChangeAbilityDescriptionNode : public ability::AbilityNode
	{
		//change ad, permantlly change ability
	public:
		ChangeAbilityDescriptionNode();

		int effect(unit::Unit* p_target, const std::string& p_abilityName, const std::string& p_valueName, int p_value);
	};

	class ChangeAbilityInfoNode : public ability::AbilityNode
	{
		//change value in ability info package, 
		//temporary change ability
	public:
		ChangeAbilityInfoNode();

		int effect(ability::AbilityInfoPackage* p_pack, const std::string& p_valueName, int p_value);
	};

	class SpawnUnitNode : public ability::AbilityNode
	{
	public:
		SpawnUnitNode();

		int effect(unit::UnitData* p_data);
	};

	//TO DO: implement
	class TileChangeNode : public ability::AbilityNode
	{
	public:
		TileChangeNode();
		
		int effect();
	};
}


