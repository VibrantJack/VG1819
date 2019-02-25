#include "Status.h"
#include "unit/Unit.h"
#include "unit\unitComponent\UnitStatusIcons.h"
#include <iostream>

namespace ability
{
	int Status::effect()
	{
		return -1;
	}
	int Status::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
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
		std::cout << "Name: "<< m_name << std::endl;
		std::cout << "ID: " << m_Id << std::endl;
		std::cout << "Description: " << m_description << std::endl;
		std::cout << "Attached Unit: " << m_unit->m_name << std::endl;
		
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

	void Status::changeName(const std::string & p_msg)
	{
		m_name = p_msg;
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
		if (p_value > 0)
		{
			m_statusType = StatusType::Stat_Buff;
		}
		else
		{
			m_statusType = StatusType::Stat_Debuff;
		}

		if (m_attributeChange.find(p_key) == m_attributeChange.end())
		{
			m_attributeChange.insert(std::make_pair(p_key, p_value));
		}
		else
		{
			m_attributeChange.at(p_key) = p_value;
		}
	}

	void Status::addTimePoint(const TimePointEvent::TPEventType& p_value)
	{
		m_TPList.push_back(p_value);
	}

	void Status::endEffectAt(const TimePointEvent::TPEventType& p_value)
	{
		m_endEffectEvent = p_value;

		addTimePoint(m_endEffectEvent);
	}

	std::vector<ability::TimePointEvent::TPEventType> Status::getTPlist()
	{
		return m_TPList;
	}

	void Status::attach(unit::Unit * p_u, bool p_nonLevelUpStatus)
	{
		m_unit = p_u; 
		p_u->getStatusContainer()->addStatus(this);

		registerTPEvent();

		// Avoids the scenario during databank setup where level up statuses are attached to a
		// Unit component without an attached GO
		if (p_nonLevelUpStatus)
		{
			auto statusIconsComp = m_unit->getGameObject().getComponent<unit::UnitStatusIcons>();
			if (statusIconsComp != nullptr)
			{
				statusIconsComp->addStatus(this);
			}
		}

		effect();
	}

	void Status::removeThis()
	{
		m_unit->getStatusContainer()->queueRemove(this);
		auto statusIconsComp = m_unit->getGameObject().getComponent<unit::UnitStatusIcons>();
		if (statusIconsComp != nullptr)
		{
			statusIconsComp->removeStatus(this);
		}
	}

	int Status::changeCounter(const std::string & p_cName, int p_value)
	{
		if (m_counter.find(p_cName) != m_counter.end())
		{
			m_counter.at(p_cName) += p_value;
			return 0;
		}
		//not find target counter
		return 1;
	}

	void Status::checkDuration(const TimePointEvent::TPEventType& p_type)
	{

		if (m_counter.find(UNIT_DURATION) != m_counter.end())
		{
			if (m_endEffectEvent == p_type)
				changeCounter();

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