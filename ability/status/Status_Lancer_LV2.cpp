#pragma once
#include "ability/status/Status.h"
#include "unit/Unit.h"
#include "board/tile/TileInfo.h"
//Rock

namespace ability
{
	Status_Lancer_LV2::Status_Lancer_LV2() : Status_LV::Status_LV()
	{
		m_Id = STATUS_LANCER_LV2;
		addTimePoint(TimePointEvent::Level_Up);
	}

	int Status_Lancer_LV2::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Turn_Start && m_active)
		{
			//demonic restriction: will not generate armor
			//only on demonic presence, it will generate armor
			if (m_unit->getTile()->getComponent<TileInfo>()->isDemonicPresence())
			{
				generateArmor();
			}
			return 0;
		}
		else if (!m_active)
		{
			if (Status_LV::effect(p_type, p_event) == 0)
			{
				m_active = true;

				addTimePoint(TimePointEvent::Turn_Start);

				unit::StatusContainer* sc = m_unit->getStatusContainer();
				sc->registerTP(TimePointEvent::Turn_Start, this);
				//sc->deregisterTP(TimePointEvent::Level_Up, this);
				return 0;
			}
		}
		return 1;
	}

	void Status_Lancer_LV2::generateArmor()
	{
		//check if unit has armor
		Status* s = m_unit->getStatusContainer()->getStatus(STATUS_SHIELD, STATUS_LANCER_LV2);
		int armor = m_counter[STATUS_ARMOR];
		if (s)//status exist
		{
			if (s->getCounters().at(UNIT_POWER) >= armor)//unit has more armor than limit
				return;
			else
				s->addCounter(UNIT_POWER, armor);//replace its value
		}
		else//status not exist
		{
			s = StatusManager::getInstance()->findStatus(STATUS_SHIELD);//new status instance

			s->changeName(STATUS_ARMOR);
			s->m_source = STATUS_LANCER_LV2;

			s->addCounter(UNIT_POWER, armor);

			s->attach(m_unit);
		}
	}
}