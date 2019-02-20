#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	void Attach::applyStatus(AbilityInfoPackage * p_info, unit::Unit* p_unit)
	{
		//apply Status_Attach to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_ATTACH);

		//set properties: name, description, source
		addStatusInfo(se, p_info);

		//get power
		int pow = p_info->m_intValue[UNIT_POWER];

		//check target is ally or enemy
		int sourceID = p_info->m_source->m_clientId;
		int targetID = p_unit->m_clientId;
		if (sourceID != targetID)//enemy
			pow = -pow;

		//add power
		se->addCounter(UNIT_POWER, pow);
		
		//add lv
		se->addCounter(UNIT_LV, p_info->m_source->m_attributes[UNIT_LV]);


		//attach to target
		se->attach(p_unit);
		
	}

	int Attach::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//check if unit has this status
			for (unit::Unit* u : p_info->m_targets)
			{
				if (!u->getStatusContainer()->getStatus(STATUS_ATTACH, m_name))
				{
					applyStatus(p_info, u);
					p_info->m_source->simpleDestroy();
				}
			}
		}

		done(p_info);

		return 0;
	}

}