#include "Status.h"
#include "unit/Unit.h"
#include <iostream>

namespace ability
{
	int Status::effect()
	{
		return -1;
	}
	int Status::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		return -1;
	}

	void Status::registerTPEvent()
	{
		for (int i = 0; i < m_TPList.size(); i++)
		{
			unit::StatusContainer* sc = m_unit->getStatusContainer();
			TimePointEvent::TPEventType type = m_TPList[i];
			sc->registerTP(type,this);
		}
	}

	void Status::print()
	{
		std::cout << m_name << std::endl;
		std::cout << m_description << std::endl;
		
		std::cout << "Counter: " << std::endl;
		for (auto it = m_counter.begin(); it != m_counter.end(); it++)
		{
			std::cout << "\t" << it->first << " : " << it->second << std::endl;
		}
		std::cout << "attributeChange: " << std::endl;
		for (auto it = m_attributeChange.begin(); it != m_attributeChange.end(); it++)
		{
			std::cout << "\t" << it->first << " : " << it->second << std::endl;
		}
	}

	Status::Status()
	{
	}
	Status::~Status()
	{

	}

	void Status::changeLV(int p_lv)
	{
		m_LV = p_lv;
	}

	void Status::changeDescription(const std::string & p_msg)
	{
		m_description = p_msg;
	}

	void Status::setEffectedAD(const std::string & p_msg)
	{
		m_effectedAD = p_msg;
	}

	void Status::addCounter(const std::string & p_key, int p_value)
	{
		if (m_counter.find(p_key) == m_counter.end())
		{
			m_counter.insert(std::make_pair(p_key, p_value));
		}
		else
		{
			m_counter.at(p_key) = p_value;
		}

	}

	void Status::addAttributeChange(const std::string & p_key, int p_value)
	{
		if (m_attributeChange.find(p_key) == m_attributeChange.end())
		{
			m_attributeChange.insert(std::make_pair(p_key, p_value));
		}
		else
		{
			m_attributeChange.at(p_key) = p_value;
		}
	}

	void Status::addTimePoint(ability::TimePointEvent::TPEventType p_value)
	{
		m_TPList.push_back(p_value);
	}

	std::vector<ability::TimePointEvent::TPEventType> Status::getTPlist()
	{
		return m_TPList;
	}

	void Status::attach(unit::Unit * p_u)
	{
		m_unit = p_u; 
		p_u->getStatusContainer()->addStatus(this);

		registerTPEvent();

		effect();
	}

	void Status::removeThis()
	{
		m_unit->getStatusContainer()->queueRemove(this);
	}

	int Status::changeCounter(const std::string & p_cName, int p_value)
	{
		if (m_counter.find(p_cName) != m_counter.end())
		{
			m_counter.at(p_cName) += p_value;
			if (p_cName == UNIT_DURATION)
				checkDuration();
			return 0;
		}
		//not find target counter
		return 1;
	}

	void Status::checkDuration()
	{
		if (m_counter.find(UNIT_DURATION) != m_counter.end())
		{
			if (m_counter.at(UNIT_DURATION) <= 0)
			{
				effectEnd();
				removeThis();
			}
		}
	}

	void Status::effectEnd()
	{
	}
}

