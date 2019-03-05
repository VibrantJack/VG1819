#pragma once
#include "ability/status/statusLV/Status_LV.h"
#include "unit/Unit.h"
#include "board/tile/TileInfo.h"
//Rock

namespace ability
{
	Status_Evil_Fiend_LV::Status_Evil_Fiend_LV() : Status_LV::Status_LV()
	{
		m_Id = STATUS_EVIL_FIEND_LV;
		//addTimePoint(TimePointEvent::Level_Up);
	}

	int Status_Evil_Fiend_LV::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (Status_LV::effect(p_type, p_event) == 0)
		{
			//full heal hp if in DP
			
			//get dp
			TileInfo* info = m_unit->getTile()->getComponent<TileInfo>();
			if (!info->isDemonicPresence())
				return 0;

			//in DP
			AbilityNode* node = AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

			//get max hp
			int maxhp = m_unit->m_attributes[UNIT_MAX_HP];
			//gain max hp
			node->effect(m_unit, UNIT_HP, maxhp);


			return 0;
		}
		return 1;
	}
}