#pragma once
#include "ability/AbilityInfoPackage.h"
#include "ability/node/AbilityNodeManager.h"
#include "ability/StatusManager.h"
#include "ability/status/statusEvent/TimePointEvent.h"
#include "ability/AbilityMacro.h"
#include <string>
#include <unordered_map>
#include <vector>

//Rock

namespace ability
{
	class Ability
	{
	public:
		Ability() {};
		virtual ~Ability() {};

		std::string m_name;

		virtual int effect(AbilityInfoPackage* p_info) = 0;
		virtual void singleTargetProjectileFinished(AbilityInfoPackage* p_package);
	protected:
		//simple ability
		void singleTargetDamage(AbilityInfoPackage* p_info);
		void multiTargetDamage(AbilityInfoPackage* p_info);
		int damage(unit::Unit* p_target, int power);

		//delete package and tell unit it acts once
		void done(const AbilityInfoPackage* p_info);
		//remove cost counter
		void removeCounter(unit::Unit* p_target, const std::string& p_name, int p_n);
		//check is there targets in package
		bool checkTarget(const AbilityInfoPackage* p_info);
		//check if target unit is ally
		bool checkAlly(unit::Unit* p_source, unit::Unit* p_target);
		//check if unit has the tag
		bool checkTag(unit::Unit* p_u, const std::string& p_tag);

		//get targets from tiles in the info package,
		//for cast time ability which units may move in and out the range
		void getTarget(AbilityInfoPackage* p_info);

		//trigger time point event
		void triggerTPEvent(ability::TimePointEvent::TPEventType p_tp, unit::Unit* p_target, AbilityInfoPackage* p_info);
	};

	class Move : public Ability
	{
	public:
		std::string m_name = ACTION_MOVE;
		int effect(AbilityInfoPackage* p_info);
	};

	class Join : public Ability
	{
	public:
		std::string m_name = ACTION_JOIN;
		int effect(AbilityInfoPackage* p_info);
	};

	class ManipulateTile : public Ability
	{
	public:
		std::string m_name = ABILITY_MANIPULATE_TILE;
		int effect(AbilityInfoPackage* p_info);
	};

	class Heal : public Ability
	{
	public:
		std::string m_name = ABILITY_HEAL;
		int effect(AbilityInfoPackage* p_info);
	};

	class Fight : public Ability
	{
	public:
		std::string m_name = ABILITY_FIGHT;
		int effect(AbilityInfoPackage* p_info) { singleTargetDamage(p_info); return 0; };
	};

	class Shoot : public Ability
	{
	public:
		std::string m_name = ABILITY_SHOOT;
		int effect(AbilityInfoPackage* p_info) { singleTargetDamage(p_info); return 0; };
	};

	class Encourage : public Ability
	{
	private:
		void applyStatus(AbilityInfoPackage* p_info);
		void stackStatus(AbilityInfoPackage* p_info);
	public:
		std::string m_name = ABILITY_ENCOURAGE;
		int effect(AbilityInfoPackage* p_info);
	};

	class QuickShoot : public Ability
	{
	public:
		std::string m_name = ABILITY_QUICK_SHOOT;
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info); return 0; };
	};

	class Sabotage : public Ability
	{
	public:
		std::string m_name = ABILITY_SABOTAGE;
		int effect(AbilityInfoPackage* p_info);
	};

	class Build_the_Wall : public Ability
	{
	private:
		int m_unitIndex = 5;
	public:
		std::string m_name = ABILITY_BUILD_WALL;
		int effect(AbilityInfoPackage* p_info);
	};

	class Defend : public Ability
	{
	private:
		void applyStatus(AbilityInfoPackage* p_info);
		void stackStatus(AbilityInfoPackage* p_info);
	public:
		std::string m_name = ABILITY_DEFEND;
		int effect(AbilityInfoPackage* p_info);
	};

	class Slay : public Ability
	{
	public:
		std::string m_name = ABILITY_SLAY;
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info); return 0; };
	};

	class SummonUnit : public Ability
	{
	public:
		std::string m_name = ABILITY_SUMMON_UNIT;
		int effect(AbilityInfoPackage* p_info);
	};

	class Blast : public Ability
	{
	public:
		std::string m_name = ABILITY_BLAST;
		int effect(AbilityInfoPackage* p_info) 
		{
			getTarget(p_info);
			multiTargetDamage(p_info); 
			return 0; 
		};
	};

	class Burn : public Ability
	{
	public:
		std::string m_name = ABILITY_BURN;
		int effect(AbilityInfoPackage* p_info) { singleTargetDamage(p_info); return 0; };
	};

	class FireDance : public Ability
	{
	public:
		std::string m_name = ABILITY_FIRE_DANCE;
		int effect(AbilityInfoPackage* p_info)
		{
			getTarget(p_info);
			multiTargetDamage(p_info);
			return 0;
		};
	};

	class Fire : public Ability
	{
	public:
		std::string m_name = ABILITY_FIRE;
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info); return 0; };
	};

	class Load : public Ability
	{
	private:
		void applyStatus(AbilityInfoPackage* p_info);
	public:
		std::string m_name = ABILITY_LOAD;
		int effect(AbilityInfoPackage* p_info);
	};

	class Arm : public Ability
	{
	public:
		std::string m_name = ABILITY_ARM;
		int effect(AbilityInfoPackage* p_info);
	};

	class Volley : public Ability
	{
	public:
		std::string m_name = ABILITY_VOLLEY;
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info); return 0; };
	};

	class TheLight : public Ability
	{
	public:
		std::string m_name = ABILITY_THE_LIGHT;
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info); return 0; };
	};

	class EnergyControl : public Ability
	{
	public:
		std::string m_name = ABILITY_ENERGY_CONTROL;
		int effect(AbilityInfoPackage* p_info);
	};

	class PowerSlam : public Ability
	{
	public:
		std::string m_name = ABILITY_POWER_SLAM;
		int effect(AbilityInfoPackage* p_info);
	};

	class PowerSurge : public Ability
	{
	public:
		std::string m_name = ABILITY_POWER_SURGE;
		int effect(AbilityInfoPackage* p_info);
	};

	class Rally : public Ability
	{
	public:
		std::string m_name = ABILITY_RALLY;
		int effect(AbilityInfoPackage* p_info);
	};

	class HereHomeland : public Ability
	{
	public:
		std::string m_name = ABILITY_HOMELAND;
		int effect(AbilityInfoPackage* p_info);
	};
}


