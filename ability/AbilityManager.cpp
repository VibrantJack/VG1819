#include "AbilityManager.h"
#include "ability/Heal.h"

//Rock

namespace ability
{
	AbilityManager* AbilityManager::sm_instance = nullptr;

	void AbilityManager::init()
	{
		Ability* newAbility;

		//TO DO: need improve
		newAbility = new Heal();
		newAbility->m_name = "Heal";
		newAbility->m_description = "Heal target 4 HP";
		m_abilityList.push_back(newAbility);
	}

	AbilityManager::AbilityManager()
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
		return findAbility(p_name)->effect(p_info);
	}

}
