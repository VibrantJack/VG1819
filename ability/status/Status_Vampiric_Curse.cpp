#pragma once
#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
//Rock

namespace ability
{
	Status_Vampiric_Curse::Status_Vampiric_Curse() : Status::Status()
	{
		m_Id = STATUS_VAMPIRIC_CURSE;
		m_statusType = StatusType::Stat_Debuff;
		endEffectAt();
	}

	int Status_Vampiric_Curse::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == m_endEffectEvent)
		{
			//steal hp

			//get power
			int power = m_intValue[UNIT_POWER];

			//get node
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

			//target lose hp
			node->effect(m_unit, UNIT_HP, -power);

			//caster gain hp
			if(m_caster != nullptr)
				node->effect(m_caster, UNIT_HP, power);
			
			checkDuration();

			return 0;
		}
		return 1;
	}
}