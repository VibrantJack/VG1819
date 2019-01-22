#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	void FearStrike::applyStatus(AbilityInfoPackage * p_info, unit::Unit* p_unit)
	{
		//reduce target IN to 1

		//apply Status_Temp_Change to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_TEMP_CHANGE);

		//set properties: name, description, source
		addStatusInfo(se, p_info);

		//get target base initiative
		int in = p_unit->m_attributes[UNIT_BASE_IN];
		int deltaIN = -(in - 1); //reduced to 1

		se->addAttributeChange(UNIT_IN, deltaIN);
		se->addCounter(UNIT_DURATION, 1);

		//attach to target
		se->attach(p_unit);
	}

	int FearStrike::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//check if unit has this status
			for (unit::Unit* u : p_info->m_targets)
			{
				if (!u->getStatusContainer()->getStatus(STATUS_TEMP_CHANGE, m_name))//doesn't have status
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