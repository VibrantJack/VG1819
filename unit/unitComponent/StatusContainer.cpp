#pragma once
#include "StatusContainer.h"
#include "unit/UnitMonitor.h"

namespace unit
{
	StatusContainer::StatusContainer(Unit* p_unit)
		:m_unit(p_unit)
	{
		m_TPStatusList = new std::unordered_map<ability::TimePointEvent::TPEventType, std::vector<ability::Status*>*>();
	}

	StatusContainer::~StatusContainer()
	{
		for (auto it = m_statusList.begin(); it != m_statusList.end(); ++it)
		{
			delete *it;
		}

		m_statusList.clear();

		for (auto it : *m_TPStatusList ) 
		{
			delete it.second;
		}

		delete m_TPStatusList;
	}

	void unit::StatusContainer::addStatus(ability::Status * p_newStatus)
	{
		m_statusList.push_back(p_newStatus);
		//unit::UnitMonitor().getInstanceSafe()->printStatus(this);
	}

	void StatusContainer::queueRemove(ability::Status * p_oldStatus)
	{
		m_removeQueue.push_back(p_oldStatus);
	}

	bool unit::StatusContainer::removeStatus(const ability::Status * p_oldStatus)
	{
		for (auto it = m_statusList.begin(); it != m_statusList.end(); it++)
		{
			if ((*it) == p_oldStatus)
			{
				std::vector<ability::TimePointEvent::TPEventType> list = (*it)->getTPlist();
				for (int i = 0; i < list.size(); i++)
				{
					deregisterTP(list[i], *it);
				}

				delete *it;
				m_statusList.erase(it);

				return true;
			}
		}
		return false;
	}

	ability::Status * StatusContainer::getStatus(const std::string & p_Id, const std::string& p_source)
	{
		for (ability::Status* it : m_statusList)
		{
			if (it->getID() == p_Id)
			{
				//if no source specified, then any source apply this status will be returned
				if(it->m_source == p_source || p_source == "ANY")
					return it;
			}
		}
		return nullptr;
	}

	void StatusContainer::registerTP(ability::TimePointEvent::TPEventType p_type, ability::Status * p_status)
	{
		//check if there is a list for this type
		if (m_TPStatusList->find(p_type) == m_TPStatusList->end())
		{//create a list for this type
			m_TPStatusList->insert(std::make_pair(p_type, new std::vector<ability::Status*>()));
		}
		//get the list
		std::vector<ability::Status*>* statuslist = m_TPStatusList->at(p_type);
		//check if the status exist in the list
		for (auto it = statuslist->begin(); it != statuslist->end(); it++)
		{
			if ((*it) == p_status)//has duplicate, ignore it
			{
				return;
			}
		}
		//not exist, add it to list
		statuslist->push_back(p_status);
		
	}

	void StatusContainer::deregisterTP(ability::TimePointEvent::TPEventType p_type, ability::Status * p_status)
	{
		//check if there is a list for this type
		if (m_TPStatusList->find(p_type) == m_TPStatusList->end())
		{
			assert(false);//it's not registered
		}
		//get the list
		std::vector<ability::Status*>* statuslist = m_TPStatusList->at(p_type);
		//check if the status exist in the list
		for (auto it = statuslist->begin(); it != statuslist->end(); it++)
		{
			if ((*it) == p_status)//found, remove it
			{
				statuslist->erase(it);
				return;
			}
		}
		//not exist
		assert(false);
	}

	void StatusContainer::triggerTP(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent* p_event)
	{
		//check if there is a list for this type
		auto found = m_TPStatusList->find(p_type);
		if (found == m_TPStatusList->end())
		{
			return;
		}
		//get the list
		std::vector<ability::Status*>* statuslist = found->second;

		//all status in the list take effect
		for (auto it = statuslist->begin(); it != statuslist->end(); it++)
		{
			(*it)->effect(p_type,p_event);
		}

		for (int i = 0; i < m_removeQueue.size(); i++)
		{
			removeStatus(m_removeQueue[i]);
		}
		m_removeQueue.clear();
	}
	Unit * StatusContainer::getUnit()
	{
		return m_unit;
	}
}

