#include "UnitMonitor.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"
#include <iostream>

//Rock

namespace unit
{
	UnitMonitor* UnitMonitor::m_instance = nullptr;

	void UnitMonitor::printStatus(unit::StatusContainer* p_s)
	{
		for (auto it : p_s->m_statusList)
		{
			it->print();
		}
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
		for (auto it : p_u->m_attributes)
		{
			std::cout << it.first << " : " << it.second << std::endl;
		}

		//size
		std::cout << "Size: " << p_u->m_size << std::endl;

		std::cout << "Ability: " << std::endl;
		for (auto it : p_u->m_ADList)
		{
			std::cout << it.first << std::endl;
			for (auto it2 : it.second->m_stringValue)
			{
				std::cout << it2.first << " : " << it2.second << std::endl;
			}
			for (auto it2 : it.second->m_intValue)
			{
				std::cout << it2.first << " : " << it2.second << std::endl;
			}
		}
		std::cout << "Status: " << std::endl;
		printStatus(p_u->getStatusContainer());
		std::cout << std::endl;
	}

	void UnitMonitor::printIT()
	{
		InitiativeTracker* tracker = InitiativeTracker::getInstance();

		for (auto it : tracker->getUnitList())
		{
			std::string name = it->getComponent<unit::Unit>()->m_name;
			int i = it->getComponent<unit::Unit>()->m_attributes["in"];
			std::cout << "Unit: "<< name<<" \tin: "<< i << std::endl;
		}
	}

}
