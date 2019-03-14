#include "ability/ability/Ability.h"
#include "unit/Unit.h"
#include "_Project\UniversalPfx.h"
//Rock

namespace ability
{
	int Sabotage::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//damage target by power

			//trigger deal damage event
			triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

			unit::Unit* target = p_info->m_targets[0];

			if (target->checkTag(STRUCTURE) || target->checkTag(MACHINE))
			{
				triggerTPEvent(ability::TimePointEvent::Receive_Damage, target, p_info);

				int power = -(p_info->m_intValue.find(UNIT_POWER)->second);

				changeHP(target, power);

				UniversalSounds::playSound("deconstruction");
				UniversalPfx::getInstance()->playEffect("Sabotage", target->getTransform().getTranslation());

			}

		}
		//delete package
		done(p_info);
		
		//target isn't structure
		return 1;
	}

}