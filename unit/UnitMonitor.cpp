#include "UnitMonitor.h"
#include <iostream>

UnitMonitor* UnitMonitor::m_instance = nullptr;

void UnitMonitor::printAbility(Ability * p_a)
{
	//TO DO
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

	std::cout << "HP: " << p_u->m_HP << std::endl;
	std::cout << "IN: " << p_u->m_IN << std::endl;
	std::cout << "MV: " << p_u->m_MV << std::endl;
	std::cout << "Cost: " << p_u->m_Cost << std::endl;
	std::cout << "Size: " << p_u->m_size << std::endl;
	std::cout << "LV: " << p_u->m_LV << std::endl;

	std::cout << "Counter: ";
	for (std::pair<std::string,int> entry : p_u->m_Counter)
	{
		std::cout << "\t" << entry.first << " : " << entry.second << std::endl;
	}
	
	std::cout << "Ability: ";
	for (int i = 0; i < p_u->m_Ability.size(); i++)
	{
		printAbility(p_u->m_Ability[i]);
	}
	std::cout << std::endl;

	std::cout << "Status: ";
	for (int i = 0; i < p_u->m_Status.size(); i++)
	{
		printStatus(p_u->m_Status[i]);
	}
	std::cout << std::endl;
}
