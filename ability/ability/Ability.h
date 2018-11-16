#pragma once
#include "ability/AbilityInfoPackage.h"
#include "ability/node/AbilityNodeManager.h"
#include "ability/StatusManager.h"
#include "ability/status/statusEvent/TimePointEvent.h"
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

	protected:
		//simple ability
		int damage(unit::Unit* p_target, int power);

		//delete package and tell unit it acts once
		void done(const AbilityInfoPackage* p_info);

		//check is there targets in package
		bool checkTarget(const AbilityInfoPackage* p_info);

		//get targets from tiles in the info package,
		//for cast time ability which units may move in and out the range
		void getTarget(AbilityInfoPackage* p_info);

		//trigger time point event
		void triggerTPEvent(ability::TimePointEvent::TPEventType p_tp, unit::Unit* p_target, AbilityInfoPackage* p_info);
	};

	class Move : public Ability
	{
	public:
		Move();
		virtual ~Move();
		int effect(AbilityInfoPackage* p_info);
	};

	class Join : public Ability
	{
	public:
		int effect(AbilityInfoPackage* p_info);
	};

	class ManipulateTile : public Ability
	{
	public:
		ManipulateTile();
		virtual ~ManipulateTile();
		int effect(AbilityInfoPackage* p_info);
	};

	class Heal : public Ability
	{
	public:
		Heal();
		virtual ~Heal();
		int effect(AbilityInfoPackage* p_info);
	};

	class Fight : public Ability
	{
	public:
		Fight();
		virtual ~Fight();
		int effect(AbilityInfoPackage* p_info);
	};

	class Shoot : public Ability
	{
	public:
		Shoot();
		virtual ~Shoot();
		int effect(AbilityInfoPackage* p_info);
	};

	class Encourage : public Ability
	{
	private:
		void applyStatus(AbilityInfoPackage* p_info);
		void stackStatus(AbilityInfoPackage* p_info);
	public:
		Encourage();
		virtual ~Encourage();
		int effect(AbilityInfoPackage* p_info);
	};

	class QuickShoot : public Ability
	{
	public:
		QuickShoot();
		virtual ~QuickShoot();
		int effect(AbilityInfoPackage* p_info);
	};

	class Sabotage : public Ability
	{
	public:
		Sabotage();
		virtual ~Sabotage();
		int effect(AbilityInfoPackage* p_info);
	};

	class Build_the_Wall : public Ability
	{
	private:
		unit::UnitData* m_wallData;
	public:
		Build_the_Wall();
		virtual ~Build_the_Wall();
		int effect(AbilityInfoPackage* p_info);
	};

	class Dodge : public Ability
	{
	private:
		void applyStatus(AbilityInfoPackage* p_info);
		void stackStatus(AbilityInfoPackage* p_info);
	public:
		Dodge();
		virtual ~Dodge();
		int effect(AbilityInfoPackage* p_info);
	};

	class Slay : public Ability
	{
	public:
		Slay();
		virtual ~Slay();
		int effect(AbilityInfoPackage* p_info);
	};

	class SummonUnit : public Ability
	{
	public:
		SummonUnit();

		int effect(AbilityInfoPackage* p_info);
	};

	class Blast : public Ability
	{
	public:
		int effect(AbilityInfoPackage* p_info);
	};
}


