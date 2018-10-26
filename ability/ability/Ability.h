#pragma once
#include "ability/AbilityInfoPackage.h"
#include "ability/node/AbilityNodeManager.h"
#include "ability/StatusManager.h"

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

		virtual int effect(const AbilityInfoPackage* p_info) = 0;

	protected:
		//simple ability
		int damage(unit::Unit* p_target, int power);
		//delete package and tell unit it acts once
		void done(const AbilityInfoPackage* p_info);
	};

	class Move : public Ability
	{
	public:
		Move();
		virtual ~Move();
		int effect(const AbilityInfoPackage* p_info);
	};

	class ManipulateTile : public Ability
	{
	public:
		ManipulateTile();
		virtual ~ManipulateTile();
		int effect(const AbilityInfoPackage* p_info);
	};

	class Heal : public Ability
	{
	public:
		Heal();
		virtual ~Heal();
		int effect(const AbilityInfoPackage* p_info);
	};

	class Fight : public Ability
	{
	public:
		Fight();
		virtual ~Fight();
		int effect(const AbilityInfoPackage* p_info);
	};

	class Shoot : public Ability
	{
	public:
		Shoot();
		virtual ~Shoot();
		int effect(const AbilityInfoPackage* p_info);
	};

	class Encourage : public Ability
	{
	private:
		void applyStatus(const AbilityInfoPackage* p_info);
		void stackStatus(const AbilityInfoPackage* p_info);
	public:
		Encourage();
		virtual ~Encourage();
		int effect(const AbilityInfoPackage* p_info);
	};

	class QuickShoot : public Ability
	{
	public:
		QuickShoot();
		virtual ~QuickShoot();
		int effect(const AbilityInfoPackage* p_info);
	};

	class Sabotage : public Ability
	{
	public:
		Sabotage();
		virtual ~Sabotage();
		int effect(const AbilityInfoPackage* p_info);
	};

	class Build_the_Wall : public Ability
	{
	private:
		unit::UnitData* m_wallData;
	public:
		Build_the_Wall();
		virtual ~Build_the_Wall();
		int effect(const AbilityInfoPackage* p_info);
	};

	class Dodge : public Ability
	{
	private:
		void applyStatus(const AbilityInfoPackage* p_info);
		void stackStatus(const AbilityInfoPackage* p_info);
	public:
		Dodge();
		virtual ~Dodge();
		int effect(const AbilityInfoPackage* p_info);
	};

	class Slay : public Ability
	{
	public:
		Slay();
		virtual ~Slay();
		int effect(const AbilityInfoPackage* p_info);
	};

	class SummonUnit : public Ability
	{
	public:
		SummonUnit();

		int effect(const AbilityInfoPackage* p_info);
	};
}


