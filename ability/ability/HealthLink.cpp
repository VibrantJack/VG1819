#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	void HealthLink::applyStatus(AbilityInfoPackage * p_info, unit::Unit* p_unit)
	{
		//apply Status_Attach to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_VAMPIRIC_CURSE);
		Status_Vampiric_Curse* s = static_cast<Status_Vampiric_Curse*>(se);

		//set properties: name, description, source
		addStatusInfo(s, p_info);

		//get power
		int pow = p_info->m_intValue[UNIT_POWER];
		s->addCounter(UNIT_POWER, pow);

		//get duration
		int dur = p_info->m_intValue[UNIT_DURATION];
		s->addCounter(UNIT_DURATION, dur);

		//end at turn start
		s->endEffectAt(TimePointEvent::Turn_Start);

		//set caster
		s->setCaster(p_info->m_source);

		//attach to target
		se->attach(p_unit);

	}

	int HealthLink::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//check if unit has this status
			for (unit::Unit* u : p_info->m_targets)
			{
				if (!u->getStatusContainer()->getStatus(STATUS_VAMPIRIC_CURSE, m_name))//doesn't have status
				{
					applyStatus(p_info, u);
				}
			}
		}

		//delete package
		done(p_info);

		return 0;
	}
}