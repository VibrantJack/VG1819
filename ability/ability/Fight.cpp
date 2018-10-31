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
		//trigger deal damage event
		unit::StatusContainer* sc = p_info->m_source->getStatusContainer();
		ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::Deal_Damage);
		t->putPackage(INFO_PACKAGE_KEY, p_info);
		sc->triggerTP(ability::TimePointEvent::Deal_Damage, t);
		//trigger receive damage event
		//damage target by power
		unit::Unit* target = p_info->m_target;

		//so power will change to negative
		int power = -(p_info->m_intValue.find("power")->second);

		damage(target,power);

		return 0;
	}

}
