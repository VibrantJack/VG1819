#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	void Arm::applyStatus(AbilityInfoPackage* p_info)
	{
		//apply Status_Encourage to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_SHIELD);

		//set properties
		int pow = p_info->m_intValue.find(UNIT_POWER)->second;

		se->addCounter(UNIT_POWER, pow);

		//attach to target
		se->attach(p_info->m_targets[0]);
	}

	Arm::Arm()
	{
	}

	Arm::~Arm()
	{
	}

	int Arm::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			for (auto it : p_info->m_targets)
			{
				if (!p_info->m_targets[0]->getStatusContainer()->getStatus(STATUS_SHIELD))
					applyStatus(p_info);
			}
		}

		//delete package
		done(p_info);

		return 0;
	}

}