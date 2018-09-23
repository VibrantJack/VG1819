#include "UnitMonitor.h"
#include <iostream>

//Rock

namespace unit
{
	UnitMonitor* UnitMonitor::m_instance = nullptr;

	void UnitMonitor::printStatus(ability::Status * p_s)
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

		//size
		std::cout << "Size: " << p_u->m_size << std::endl;

		//std::cout << "Status: ";
		//for (int i = 0; i < p_u->m_Status.size(); i++)
		//{
		//	printStatus(p_u->m_Status[i]);
		//}
		std::cout << std::endl;
	}

}
