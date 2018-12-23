#pragma once
#include "AbilityManager.h"

// Networking
#include "networking\ClientGame.h"

//Rock

namespace ability
{
	AbilityManager* AbilityManager::sm_instance = nullptr;

	void AbilityManager::init()
	{
		Ability* newAbility;

		//TO DO: need improve
		newAbility = new Heal();
		m_abilityList[ABILITY_HEAL] = newAbility;

		newAbility = new Fight();
		m_abilityList[ABILITY_FIGHT] = newAbility;

		newAbility = new ManipulateTile();
		m_abilityList[ABILITY_MANIPULATE_TILE] = newAbility;

		newAbility = new Shoot();
		m_abilityList[ABILITY_SHOOT] = newAbility;

		newAbility = new Sabotage();
		m_abilityList[ABILITY_SABOTAGE] = newAbility;

		newAbility = new Build_the_Wall();
		m_abilityList[ABILITY_BUILD_WALL] = newAbility;

		newAbility = new Encourage();
		m_abilityList[ABILITY_ENCOURAGE] = newAbility;

		newAbility = new QuickShoot();
		m_abilityList[ABILITY_QUICK_SHOOT] = newAbility;

		newAbility = new Slay();
		m_abilityList[ABILITY_SLAY] = newAbility;

		newAbility = new Defend();
		m_abilityList[ABILITY_DEFEND] = newAbility;

		newAbility = new SummonUnit();
		m_abilityList[ABILITY_SUMMON_UNIT] = newAbility;

		newAbility = new Move();
		m_abilityList[ACTION_MOVE] = newAbility;

		newAbility = new Blast();
		m_abilityList[ABILITY_BLAST] = newAbility;

		newAbility = new Join();
		m_abilityList[ACTION_JOIN] = newAbility;

		newAbility = new Burn();
		m_abilityList[ABILITY_BURN] = newAbility;

		newAbility = new FireDance();
		m_abilityList[ABILITY_FIRE_DANCE] = newAbility;

		newAbility = new Fire();
		m_abilityList[ABILITY_FIRE] = newAbility;

		newAbility = new Load();
		m_abilityList[ABILITY_LOAD] = newAbility;

		newAbility = new Volley();
		m_abilityList[ABILITY_VOLLEY] = newAbility;

		newAbility = new Arm();
		m_abilityList[ABILITY_ARM] = newAbility;

		newAbility = new TheLight();
		m_abilityList[ABILITY_THE_LIGHT] = newAbility;

		newAbility = new EnergyControl();
		m_abilityList[ABILITY_ENERGY_CONTROL] = newAbility;

		newAbility = new PowerSlam();
		m_abilityList[ABILITY_POWER_SLAM] = newAbility;

		newAbility = new PowerSurge();
		m_abilityList[ABILITY_POWER_SURGE] = newAbility;

		newAbility = new Rally();
		m_abilityList[ABILITY_RALLY] = newAbility;

		newAbility = new HereHomeland();
		m_abilityList[ABILITY_HOMELAND] = newAbility;
	}

	AbilityManager::AbilityManager()
	{
		init();
	}

	AbilityManager::~AbilityManager()
	{
		auto end = m_abilityList.end();
		for (auto it = m_abilityList.begin(); it != end; ++it)
		{
			delete it->second;
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
		return m_abilityList[p_name];
	}

	int AbilityManager::useAbility(const std::string & p_name, AbilityInfoPackage * p_info)
	{
		if (networking::ClientGame::isNetworkValid())
		{
			networking::ClientGame::getInstance()->sendAbilityPacket(p_name, p_info);
		}
		return findAbility(p_name)->effect(p_info);
	}

	/*
	const std::string& AbilityManager::lastAbilityUsed()
	{
		return m_sLastAbilityUsed;
	}*/

}
