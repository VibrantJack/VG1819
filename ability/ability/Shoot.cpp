#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	Shoot::Shoot()
	{
	}

	Shoot::~Shoot()
	{
	}

	int Shoot::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			unit::StatusContainer* sc = p_info->m_source->getStatusContainer();
			ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::Deal_Damage);
			t->putPackage(INFO_PACKAGE_KEY, p_info);
			sc->triggerTP(ability::TimePointEvent::Deal_Damage, t);

			//damage target by power
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