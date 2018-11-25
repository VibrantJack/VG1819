#pragma once
#include "ability/AbilityInfoPackage.h"
#include "ability/ability/Ability.h"
#include "ability/status/Status.h"
#include "AbilityMacro.h"

#include <vector>
#include <assert.h>

//Rock

namespace ability
{
	class Ability;

	class AbilityManager
	{
	private:
		static AbilityManager * sm_instance;

		std::unordered_map<std::string, Ability*> m_abilityList;
		//std::string m_sLastAbilityUsed;

		void init();

	public:
		AbilityManager();
		~AbilityManager();

		static void createInstance();
		static void destroyInstance();
		static AbilityManager* getInstance();

		Ability* findAbility(const std::string& p_name);
		int useAbility(const std::string& p_name, AbilityInfoPackage* p_info);

		//const std::string& lastAbilityUsed();
	};
}
