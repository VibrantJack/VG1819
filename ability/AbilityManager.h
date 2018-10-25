#pragma once
#include "ability/AbilityInfoPackage.h"
#include "ability/ability/Ability.h"
#include "ability/status/Status.h"

#include <vector>
#include <assert.h>

#define MANIPULATE_TILE_ABILITY "ManipulateTile"
#define HEAL_ABILITY "Heal"
#define FIGHT_ABILITY "Fight"
#define SUMMON_UNIT_ABILITY "SummonUnit"
#define DEFAULT_ABILITY "None"


//Rock

namespace ability
{
	class Ability;

	class AbilityManager
	{
	private:
		static AbilityManager * sm_instance;

		std::vector<Ability*> m_abilityList;
		std::string m_sLastAbilityUsed;

		void init();

	public:
		AbilityManager();
		~AbilityManager();

		static void createInstance();
		static void destroyInstance();
		static AbilityManager* getInstance();

		Ability* findAbility(const std::string& p_name);
		int useAbility(const std::string& p_name, AbilityInfoPackage* p_info);

		const std::string& lastAbilityUsed();
		void resetLastAbilityUsed() { m_sLastAbilityUsed = DEFAULT_ABILITY; };
	};
}
