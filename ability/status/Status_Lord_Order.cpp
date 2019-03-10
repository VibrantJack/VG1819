#pragma once
#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
//Rock

namespace ability
{
	Status_Lord_Order::Status_Lord_Order() : Status::Status()
	{
		m_Id = STATUS_LORD_ORDER;
		m_statusType = StatusType::Stat_Debuff;

		addTimePoint(TimePointEvent::Receive_Damage);
		addTimePoint(TimePointEvent::Deal_Damage);
		endEffectAt();
	}

	int Status_Lord_Order::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		checkDuration(p_type);//check duration and end this effect

		AbilityInfoPackage* pack;
		int power;
		AbilityNode* node;

		switch(p_type)
		{
		case TimePointEvent::Receive_Damage:
			//unit is damaged
			//caster gain same amount of HP

			//get pack
			pack = p_event->getPackage(INFO_PACKAGE_KEY);

			//get pack power
			power = pack->m_intValue.at(UNIT_POWER);

			//caster gain HP
			node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);
			if (m_caster != nullptr)
				node->effect(m_caster, UNIT_HP, power);

			return 0;
		case TimePointEvent::Deal_Damage:
			//unit gona deal damage
			//it doesn't matter if it actually deals damage
			//the key is it attacks

			//get pack
			pack = p_event->getPackage(INFO_PACKAGE_KEY);

			//get status power
			power = m_intValue[UNIT_POWER];

			//get node
			node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

			//unit lose hp
			node->effect(m_unit, UNIT_HP, -power);

			//targets lose hp
			for (auto u : pack->m_targets)
			{
				node->effect(u, UNIT_HP, -power);
			}
			return 0;
		}
		return 1;
	}
}