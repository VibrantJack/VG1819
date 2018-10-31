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

		newAbility = new Shoot();
		newAbility->m_name = "Shoot";
		m_abilityList.push_back(newAbility);

		newAbility = new Sabotage();
		newAbility->m_name = "Sabotage";
		m_abilityList.push_back(newAbility);

		newAbility = new Build_the_Wall();
		newAbility->m_name = "Build the Wall";
		m_abilityList.push_back(newAbility);

		newAbility = new Encourage();
		newAbility->m_name = "Encourage";
		m_abilityList.push_back(newAbility);

		newAbility = new QuickShoot();
		newAbility->m_name = "QuickShoot";
		m_abilityList.push_back(newAbility);

		newAbility = new Slay();
		newAbility->m_name = "Slay";
		m_abilityList.push_back(newAbility);

		newAbility = new Dodge();
		newAbility->m_name = "Dodge";
		m_abilityList.push_back(newAbility);

		newAbility = new SummonUnit();
		newAbility->m_name = SUMMON_UNIT;
		m_abilityList.push_back(newAbility);

		newAbility = new Move();
		newAbility->m_name = "Move";
		m_abilityList.push_back(newAbility);
	}

	AbilityManager::AbilityManager() : m_sLastAbilityUsed("NONE")
	{
		init();
	}

	AbilityManager::~AbilityManager()
	{
		auto end = m_abilityList.end();
		for (auto it = m_abilityList.begin(); it != end; ++it)
		{
			delete (*it);
		}
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
			{
				m_sLastAbilityUsed = p_name;
				return *it;
			}
		}
		return nullptr;
	}

	int AbilityManager::useAbility(const std::string & p_name, AbilityInfoPackage * p_info)
	{
		return findAbility(p_name)->effect(p_info);
	}

	const std::string& AbilityManager::lastAbilityUsed()
	{
		return m_sLastAbilityUsed;
	}

}
