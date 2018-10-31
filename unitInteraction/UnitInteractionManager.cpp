#include "UnitInteractionManager.h"
#include "unitInteraction/TileGetter.h"
#include <iostream>
#include <sstream>

UnitInteractionManager* UnitInteractionManager::sm_instance = nullptr;

void UnitInteractionManager::request(unit::Unit* p_unit, unit::AbilityDescription * p_ad)
{
	if (m_busy)
		return;

	m_busy = true;

	m_unit = p_unit;
	m_ad = p_ad;
	m_abilityName = m_ad->m_stringValue["name"];
	std::cout << "UnitInteractionManager Receive: " << p_unit->m_name << " :: " << m_abilityName << std::endl;

	//create package
	if (m_package != nullptr)
		m_package = nullptr;
	m_package = new ability::AbilityInfoPackage();

	m_package->m_source = p_unit;

	addPropertyFromADToPack();

	//ask player for targets
	m_tileGetter->requireTile(m_ad,p_unit,true);
}

void UnitInteractionManager::setTarget(std::vector<kitten::K_GameObject*> p_tileList, std::vector<unit::Unit*> p_unitList)
{
	m_package->m_targets = p_unitList;
	m_package->m_targetTilesGO = p_tileList;

	send();
}

UnitInteractionManager::UnitInteractionManager()
{
	m_package = nullptr;
	m_ad = nullptr;
	m_tileGetter = new TileGetter();

	m_busy = false;
}

UnitInteractionManager::~UnitInteractionManager()
{
	if (m_package != nullptr)
		delete m_package;

	delete m_tileGetter;
}

void UnitInteractionManager::cancel()
{
	std::cout << "UnitInteractionManager Cancel Ability" << std::endl;
	//delete package
	if (m_package != nullptr)
		delete m_package;

	m_busy = false;
}

void UnitInteractionManager::send()
{
	ability::AbilityManager::getInstance()->useAbility(m_abilityName,m_package);

	m_busy = false;
}

void UnitInteractionManager::addPropertyFromADToPack()
{
	/*
	//get power
	if (m_ad->m_intValue.find("power") != m_ad->m_intValue.end())
	{
		m_package->m_intValue["power"] = m_ad->m_intValue["power"];
	}*/

	for (auto it : m_ad->m_intValue)
	{
		m_package->m_intValue[it.first] = it.second;
	}
}
