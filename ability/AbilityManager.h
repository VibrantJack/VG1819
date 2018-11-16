#pragma once
#include "ability/AbilityInfoPackage.h"
#include "ability/ability/Ability.h"
#include "ability/status/Status.h"

#include <vector>
#include <assert.h>

#define ABILITY_MANIPULATE_TILE "ManipulateTile"
#define ABILITY_HEAL "Heal"
#define ABILITY_FIGHT "Fight"
#define ABILITY_SUMMON_UNIT "SummonUnit"
#define ABILITY_SHOOT "Shoot"
#define ABILITY_SABOTAGE "Sabotage"
#define ABILITY_BUILD_WALL "Build the Wall"
#define ABILITY_ENCOURAGE "Encourage"
#define ABILITY_QUICK_SHOOT "Quick Shoot"
#define ABILITY_SLAY "Slay"
#define ABILITY_DODGE "Dodge"
#define ABILITY_BLAST "Blast"

#define ACTION_MOVE "Move"
#define ACTION_JOIN "Join"

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
