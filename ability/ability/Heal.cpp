#pragma once
#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	Heal::Heal()
	{
	}

	Heal::~Heal()
	{
	}

	int Heal::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//trigger Heal event
			unit::StatusContainer* sc = p_info->m_source->getStatusContainer();
			ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::Heal);
			t->putPackage(INFO_PACKAGE_KEY, p_info);
			sc->triggerTP(ability::TimePointEvent::Heal, t);

			//trigger receive damage event
			unit::Unit* target = p_info->m_targets[0];
			sc = target->getStatusContainer();
			t = new ability::TimePointEvent(ability::TimePointEvent::Receive_Damage);
			t->putPackage(INFO_PACKAGE_KEY, p_info);
			sc->triggerTP(ability::TimePointEvent::Receive_Damage, t);

			//heal target by power
			int power = p_info->m_intValue.find("power")->second;

			//positive power = heal
			damage(target, power);
		}

		//delete package
		done(p_info);

		return 0;
	}

}
