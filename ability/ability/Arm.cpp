#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	int Arm::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			unit::Unit* source = p_info->m_source;
			for (auto it : p_info->m_targets)
			{
				if (!checkAlly(source, it))//not ally
					break;
				if (!it->getStatusContainer()->getStatus(STATUS_SHIELD,ABILITY_ARM))//don't have shield
				{
					//apply Status_Encourage to target
					ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_SHIELD);
					addStatusInfo(se, p_info);					
					UniversalPfx::getInstance()->playEffect("Arm", it->getTransform().getTranslation());

					//set properties
					int pow = p_info->m_intValue.find(UNIT_POWER)->second;

					se->m_source = ABILITY_ARM;
					se->addCounter(UNIT_POWER, pow);

					//attach to target
					se->attach(it);
				}
			}
		}

		//delete package
		done(p_info);

		UniversalSounds::playSound("arm");

		return 0;
	}

}