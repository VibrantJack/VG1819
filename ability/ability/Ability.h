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
}


