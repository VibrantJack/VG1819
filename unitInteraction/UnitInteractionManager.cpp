#include "UnitInteractionManager.h"
#include "unitInteraction/TileGetter.h"
#include "CounterGetter.h"
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

	bool needunit = false;
	if(m_ad->m_intValue.find("need_unit")!= m_ad->m_intValue.end())
		needunit = m_ad->m_intValue["need_unit"];

	//ask player for counter
	m_counterGetter->requireCounter(p_ad, p_unit);

	if (!m_busy)//player cancel ability in get counter stage
		return;

	//ask player for targets
	m_tileGetter->requireTile(m_ad,p_unit,needunit);
}

void UnitInteractionManager::setCounter(const std::string& p_counter, int p_n)
{
	m_package->m_intValue[p_counter] = p_n;
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
	m_counterGetter = new CounterGetter();

	m_busy = false;
}

UnitInteractionManager::~UnitInteractionManager()
{
	if (m_package != nullptr)
		delete m_package;

	delete m_tileGetter;
	delete m_counterGetter;
}

void UnitInteractionManager::cancel()
{
	std::cout << "UnitInteractionManager Cancel Ability" << std::endl;

	//delete package
	if (m_package != nullptr)
	{
		m_package->m_source->cancelAbility(m_ad);
		delete m_package;
		m_package = nullptr;
	}

	m_busy = false;
}

void UnitInteractionManager::send()
{
	if (m_ad->m_intValue.find("ct") == m_ad->m_intValue.end())//no cast time
	{
		ability::AbilityManager::getInstance()->useAbility(m_abilityName, m_package);
	}
	else
	{
		m_unit->setCast(m_ad, m_package);
	}
	m_package = nullptr;
	m_busy = false;
}

void UnitInteractionManager::addPropertyFromADToPack()
{
	for (auto it : m_ad->m_intValue)
	{
		m_package->m_intValue[it.first] = it.second;
	}
}
