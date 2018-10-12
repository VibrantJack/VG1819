#pragma once
#include "ability/AbilityInfoPackage.h"
#include "ability/node/AbilityNodeManager.h"
#include "ability/StatusManager.h"

#include <string>
#include <map>
#include <vector>

//Rock

namespace ability
{
	class Ability
	{
	public:
		Ability() {};
		~Ability() {};

		std::string m_name;

		virtual int effect(const AbilityInfoPackage* p_info) = 0;

	protected:
		//simple ability
		int damage(unit::Unit* p_target, int power);
	};

	class ManipulateTile : public Ability
	{
	public:
		ManipulateTile();

		int effect(const AbilityInfoPackage* p_info);
	};

	class Heal : public Ability
	{
	public:
		Heal();

		int effect(const AbilityInfoPackage* p_info);
	};

	class Fight : public Ability
	{
	public:
		Fight();

		int effect(const AbilityInfoPackage* p_info);
	};

	class Shoot : public Ability
	{
	public:
		Shoot();

		int effect(const AbilityInfoPackage* p_info);
	};

	class Encourage : public Ability
	{
	private:
		void applyStatus(const AbilityInfoPackage* p_info);
		void stackStatus(const AbilityInfoPackage* p_info);
	public:
		Encourage();

		int effect(const AbilityInfoPackage* p_info);
	};

	class QuickShoot : public Ability
	{
	public:
		QuickShoot();

		int effect(const AbilityInfoPackage* p_info);
	};

	class Sabotage : public Ability
	{
	public:
		Sabotage();

		int effect(const AbilityInfoPackage* p_info);
	};

	class Build_the_Wall : public Ability
	{
	private:
		unit::UnitData* m_wallData;
	public:
		Build_the_Wall();

		int effect(const AbilityInfoPackage* p_info);
	};

	class Dodge : public Ability
	{
	private:
		void applyStatus(const AbilityInfoPackage* p_info);
		void stackStatus(const AbilityInfoPackage* p_info);
	public:
		Dodge();

		int effect(const AbilityInfoPackage* p_info);
	};

	class Slay : public Ability
	{
	public:
		Slay();

		int effect(const AbilityInfoPackage* p_info);
	};

	class SummonUnit : public Ability
	{
	public:
		SummonUnit();

		int effect(const AbilityInfoPackage* p_info);
	};
}


