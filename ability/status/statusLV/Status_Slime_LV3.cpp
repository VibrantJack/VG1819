#pragma once
#include "ability/status/statusLV/Status_LV.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Status_Slime_LV3::Status_Slime_LV3() : Status_LV::Status_LV()
	{
		m_Id = STATUS_SLIME_LV3;
	}

	int Status_Slime_LV3::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent * p_event)
	{
		if (Status_LV::effect(p_type, p_event) == 0)
		{
			//check if target has status
			if (m_unit->getStatusContainer()->getStatus(STATUS_LAST_WORD_SUMMON))// have status
			{
				return 2;
			}

			//add status_last_word_summon which summon a lv1 slime
			Status_Last_Word_Summon* s = static_cast<Status_Last_Word_Summon*>(StatusManager::getInstance()->findStatus(STATUS_LAST_WORD_SUMMON));

			//set unit to summon,default level is 1	
			s->setUnitToSummon(m_unit->m_kibbleID);

			//add id
			s->m_intValue[CLIENT_ID] = m_unit->m_clientId;

			s->m_source = m_Id;
			s->changeName(m_stringValue["SLWS_name"]);
			s->changeDescription(m_stringValue["SLWS_description"]);

			//attach to self
			s->attach(m_unit);

			return 0;
		}
		return 1;
	}
}