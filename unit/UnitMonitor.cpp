#include "UnitMonitor.h"
#include <iostream>

UnitMonitor* UnitMonitor::m_instance = nullptr;

void UnitMonitor::printAbility(Ability * p_a)
{
	std::cout << p_a->m_description << std::endl;
}

void UnitMonitor::printStatus(Status * p_s)
{
	//TO DO
}

UnitMonitor::UnitMonitor()
{
}


UnitMonitor::~UnitMonitor()
{
}

UnitMonitor * UnitMonitor::getInstance()
{
	return m_instance;
}

UnitMonitor * UnitMonitor::getInstanceSafe()
{
	if (m_instance == nullptr)
		m_instance = new UnitMonitor();
	return m_instance;
}

void UnitMonitor::printUnit(Unit* p_u)
{
	std::cout << "Name: " << p_u->m_name << std::endl;
	std::cout << "ID: " << p_u->m_ID << std::endl;

	std::cout << "Tags: ";
	for (int i = 0; i < p_u->m_tags.size(); i++)
	{
		std::cout << p_u->m_tags[i] << " ";
	}
	std::cout << std::endl;

	//attributes
	std::map<std::string, int>::iterator it;
	for (it = p_u->m_attributes.begin(); it != p_u->m_attributes.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
	/*
	std::cout << "MaxHP: \t" << p_u->m_MaxHP << std::endl;
	std::cout << "HP: \t" << p_u->m_HP << std::endl;
	std::cout << "baseIN: \t" << p_u->m_baseIN << std::endl;
	std::cout << "IN: \t" << p_u->m_IN << std::endl;
	std::cout << "baseMV: \t" << p_u->m_baseMV << std::endl;
	std::cout << "MV: \t" << p_u->m_MV << std::endl;
	std::cout << "baseCost: \t" << p_u->m_baseCost << std::endl;
	std::cout << "Cost: \t" << p_u->m_Cost << std::endl;
	std::cout << "LV: \t" << p_u->m_LV << std::endl;
	*/

	//size
	std::cout << "Size: " << p_u->m_size << std::endl;

	//counter
	std::cout << "Counter: ";
	for (std::pair<std::string,int> entry : p_u->m_Counter)
	{
		std::cout << "\t" << entry.first << " : " << entry.second << std::endl;
	}
	
	std::cout << "Ability: ";
	for (int i = 0; i < p_u->m_Ability.size(); i++)
	{
		printAbility(AbilityManager::getInstance()->findAbility(p_u->m_Ability[i]) );
	}
	std::cout << std::endl;

	std::cout << "Status: ";
	for (int i = 0; i < p_u->m_Status.size(); i++)
	{
		printStatus(p_u->m_Status[i]);
	}
	std::cout << std::endl;
}
