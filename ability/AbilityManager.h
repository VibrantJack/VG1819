#pragma once
#include "AbilityInfoPackage.h"
#include "ability/Ability.h"
#include "status/Status.h"

#include <vector>
#include <assert.h>

//Rock

namespace ability
{
	class AbilityManager
	{
	private:
		static AbilityManager * sm_instance;

		std::vector<Ability*> m_abilityList;

		void init();

	public:
		AbilityManager();
		~AbilityManager();

		static void createInstance();
		static void destroyInstance();
		static AbilityManager* getInstance();

		Ability* findAbility(const std::string& p_name);
		int useAbility(const std::string& p_name, AbilityInfoPackage* p_info);
	};
}
