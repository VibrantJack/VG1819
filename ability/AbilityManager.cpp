#include "AbilityManager.h"

//Rock

namespace ability
{
	AbilityManager* AbilityManager::sm_instance = nullptr;

	void AbilityManager::init()
	{
		Ability* newAbility;

		//TO DO: need improve
		newAbility = new Heal();
		newAbility->m_name = HEAL_ABILITY;
		m_abilityList.push_back(newAbility);

		newAbility = new Fight();
		newAbility->m_name = FIGHT_ABILITY;
		m_abilityList.push_back(newAbility);

		newAbility = new ManipulateTile();
		newAbility->m_name = MANIPULATE_TILE_ABILITY;
		m_abilityList.push_back(newAbility);

	}

	AbilityManager::AbilityManager() : m_sLastAbilityUsed("NONE")
	{
		init();
	}

	AbilityManager::~AbilityManager()
	{
		m_abilityList.clear();
	}

	void AbilityManager::createInstance()
	{
		assert(sm_instance == nullptr);
		sm_instance = new AbilityManager();
	}

	void AbilityManager::destroyInstance()
	{
		assert(sm_instance != nullptr);
		delete sm_instance;
		sm_instance = nullptr;
	}

	AbilityManager * AbilityManager::getInstance()
	{
		assert(sm_instance != nullptr);
		return sm_instance;
	}


	Ability * AbilityManager::findAbility(const std::string & p_name)
	{
		for (auto it = m_abilityList.begin(); it != m_abilityList.end(); it++)
		{
			if ((*it)->m_name == p_name)
				return *it;
		}
		return nullptr;
	}

	int AbilityManager::useAbility(const std::string & p_name, AbilityInfoPackage * p_info)
	{
		m_sLastAbilityUsed = p_name;
		return findAbility(p_name)->effect(p_info);
	}

	const std::string& AbilityManager::lastAbilityUsed()
	{
		return m_sLastAbilityUsed;
	}

}
