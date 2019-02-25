#pragma once
#include "ability/AbilityInfoPackage.h"
#include "ability/node/AbilityNodeManager.h"
#include "ability/StatusManager.h"
#include "ability/status/statusEvent/TimePointEvent.h"
#include "ability/status/Status.h"
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
		virtual void multiTargetProjectileFinished(AbilityInfoPackage* p_package);
	protected:

		Ability(const std::string p_name) : m_name(p_name) {}

		//simple ability
		void singleTargetDamage(AbilityInfoPackage* p_info, bool p_fireProjectile = false);
		void multiTargetDamage(AbilityInfoPackage* p_info, bool p_fireProjectile = false);

		kitten::K_GameObject* summonToken(AbilityInfoPackage* p_info, int p_unitIndex);
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

		//add status name and description
		void addStatusInfo(Status* p_st, AbilityInfoPackage* p_info);
	};

	class Move : public Ability
	{
	public:
		Move() : Ability(ACTION_MOVE) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Join : public Ability
	{
	public:
		Join() : Ability(ACTION_JOIN) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class ManipulateTile : public Ability
	{
	public:
		ManipulateTile() : Ability(ABILITY_MANIPULATE_TILE) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Heal : public Ability
	{
	public:
		Heal() : Ability(ABILITY_HEAL) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Fight : public Ability
	{
	public:
		Fight() : Ability(ABILITY_FIGHT) {};
		int effect(AbilityInfoPackage* p_info) { singleTargetDamage(p_info); return 0; };
	};

	class Shoot : public Ability
	{
	public:
		Shoot() : Ability(ABILITY_SHOOT) {};
		int effect(AbilityInfoPackage* p_info) { singleTargetDamage(p_info, true); return 0; };
	};

	class Encourage : public Ability
	{
	private:
		void applyStatus(AbilityInfoPackage* p_info);
		void stackStatus(AbilityInfoPackage* p_info);
	public:
		Encourage() : Ability(ABILITY_ENCOURAGE) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class QuickShoot : public Ability
	{
	public:
		QuickShoot() : Ability(ABILITY_QUICK_SHOOT) {};
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info, true); return 0; };
	};

	class Sabotage : public Ability
	{
	public:
		Sabotage() : Ability(ABILITY_SABOTAGE) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Build_the_Wall : public Ability
	{
	private:
		int m_unitIndex = 5;
	public:
		Build_the_Wall() :Ability(ABILITY_BUILD_WALL) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Defend : public Ability
	{
	private:
		void applyStatus(AbilityInfoPackage* p_info);
		void stackStatus(AbilityInfoPackage* p_info);
	public:
		Defend() : Ability(ABILITY_DEFEND) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Slay : public Ability
	{
	public:
		Slay() : Ability(ABILITY_SLAY) {};
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info); return 0; };
	};

	class SummonUnit : public Ability
	{
	public:
		SummonUnit() : Ability(ABILITY_SUMMON_UNIT) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Blast : public Ability
	{
	public:
		Blast() : Ability(ABILITY_BLAST) {}
		int effect(AbilityInfoPackage* p_info) 
		{
			getTarget(p_info);
			multiTargetDamage(p_info, true); 
			return 0; 
		};
	};

	class Burn : public Ability
	{
	public:
		Burn() : Ability(ABILITY_BURN) {};
		int effect(AbilityInfoPackage* p_info) { singleTargetDamage(p_info, true); return 0; };
	};

	class FireDance : public Ability
	{
	public:
		FireDance() : Ability(ABILITY_FIRE_DANCE) {};
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
		Fire() : Ability(ABILITY_FIRE) {};
		int effect(AbilityInfoPackage* p_info) {
			getTarget(p_info);
			multiTargetDamage(p_info);
			return 0;
		};
	};

	class Load : public Ability
	{
	private:
		void applyStatus(AbilityInfoPackage* p_info);
	public:
		Load() : Ability(ABILITY_LOAD) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Arm : public Ability
	{
	public:
		Arm() : Ability(ABILITY_ARM) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Volley : public Ability
	{
	public:
		Volley() : Ability(ABILITY_VOLLEY) {};
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info); return 0; };
	};

	class TheLight : public Ability
	{
	public:
		TheLight() : Ability(ABILITY_THE_LIGHT) {};
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info); return 0; };
	};

	class EnergyControl : public Ability
	{
	public:
		EnergyControl() : Ability(ABILITY_ENERGY_CONTROL) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class PowerSlam : public Ability
	{
	public:
		PowerSlam() : Ability(ABILITY_POWER_SLAM) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class PowerSurge : public Ability
	{
	public:
		PowerSurge() : Ability(ABILITY_POWER_SURGE) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Rally : public Ability
	{
	public:
		Rally() : Ability(ABILITY_RALLY) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class HereHomeland : public Ability
	{
	public:
		HereHomeland() : Ability(ABILITY_HOMELAND) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Curse : public Ability
	{
	public:
		Curse() : Ability(ABILITY_CURSE) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Oppose : public Ability
	{
	public:
		Oppose() : Ability(ABILITY_OPPOSE) {};
		int effect(AbilityInfoPackage* p_info);
	private:
		kitten::K_GameObject* getTile(kitten::K_GameObject* p_tile, int p_length, int p_direction);
		int getDirection(const std::pair<int, int>& p_pos1, const std::pair<int, int>& p_pos2);
		bool checkTile(kitten::K_GameObject* p_tileGO, int p_movePower);
	};

	class Thrust : public Ability
	{
	public:
		Thrust() : Ability(ABILITY_THRUST) {};
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info); return 0; };
	};

	class ReleaseGas : public Ability
	{
	public:
		ReleaseGas() : Ability(ABILITY_RELEASE_GAS) {};
		int effect(AbilityInfoPackage* p_info) { multiTargetDamage(p_info); return 0; };
	};

	class FearStrike : public Ability
	{
	private:
		void applyStatus(AbilityInfoPackage* p_info, unit::Unit* p_unit);
	public:
		FearStrike() : Ability(ABILITY_FEAR_STRIKE) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Mucus : public Ability
	{
	private:
		void applyStatus(AbilityInfoPackage* p_info, unit::Unit* p_unit);
	public:
		Mucus() : Ability(ABILITY_MUCUS) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Summon : public Ability
	{
	private:
		int m_unitIndex = 19;
	public:
		Summon() :Ability(ABILITY_SUMMON) {};
		int effect(AbilityInfoPackage* p_info) 
		{
			summonToken(p_info, m_unitIndex);

			//delete package
			done(p_info);

			return 0;
		};
	};

	class Activate : public Ability
	{
	public:
		Activate() : Ability(ABILITY_ACTIVATE) {};
		int effect(AbilityInfoPackage* p_info);
	};

	class Stab : public Ability
	{
	public:
		Stab() : Ability(ABILITY_STAB) {};
		int effect(AbilityInfoPackage* p_info) { singleTargetDamage(p_info); return 0; };
	};
}


