#pragma once
#include "ability/AbilityInfoPackage.h"
#include "ability/node/AbilityNodeManager.h"
#include "ability/status/Status.h"

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

	class Encourage : public Ability
	{
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
}


