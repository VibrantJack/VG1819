#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Fight::Fight()
	{
	}

	Fight::~Fight()
	{
	}

	int Fight::effect(AbilityInfoPackage* p_info)
	{
		//damage target by power
		if (checkTarget(p_info))
		{
			//trigger deal damage event
			unit::StatusContainer* sc = p_info->m_source->getStatusContainer();
			ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::Deal_Damage);
			t->putPackage(INFO_PACKAGE_KEY, p_info);
			sc->triggerTP(ability::TimePointEvent::Deal_Damage, t);
			//trigger receive damage event
			unit::Unit* target = p_info->m_targets[0];
			sc = target->getStatusContainer();
			t = new ability::TimePointEvent(ability::TimePointEvent::Receive_Damage);
			t->putPackage(INFO_PACKAGE_KEY, p_info);
			sc->triggerTP(ability::TimePointEvent::Receive_Damage, t);

			//so power will change to negative
			int power = -(p_info->m_intValue.find("power")->second);

			damage(target, power);
		}

		//delete package
		done(p_info);

		return 0;
	}

}
