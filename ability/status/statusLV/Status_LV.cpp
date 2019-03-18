#pragma once
#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
#include "Status_LV.h"
//Rock

namespace ability
{
	Status_LV::Status_LV() : Status::Status()
	{
		m_Id = STATUS_LV;
		addTimePoint(TimePointEvent::Level_Up);
	}

	int Status_LV::effect()
	{
		//set lv
		this->changeName(LEVEL_UP);
		this->changeLV(m_intValue[UNIT_LV]);
		
		//hp
		this->setLvUpAttributes(UNIT_HP, UNIT_MAX_HP);
		//in
		this->setLvUpAttributes(UNIT_IN, UNIT_BASE_IN);
		//mv
		this->setLvUpAttributes(UNIT_MV, UNIT_BASE_MV);

		//effected ad
		setEffectedAD();

		return 0;
	}

	int Status_LV::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		int lv = p_event->getInt(UNIT_LV);
		if (p_type == ability::TimePointEvent::Level_Up && lv == m_LV)
		{
			//change attribute
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);
			for (auto it : m_attributeChange)
			{
				node->effect(m_unit, it.first, it.second);
			}
			return 0;
		}
		return 1;
	}

	void Status_LV::setLvUpAttributes(const std::string & p_attribute, const std::string & p_baseAttribute)
	{
		auto found = m_intValue.find(p_attribute);
		if (found != m_intValue.end())
		{
			int hp = found->second;
			this->addAttributeChange(p_baseAttribute, hp);
			this->addAttributeChange(p_attribute, hp);
		}
	}
}