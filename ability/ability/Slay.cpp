#include "ability/ability/Ability.h"

#include "unit/Unit.h"

//Rock

namespace ability
{
	Slay::Slay()
	{
	}

	Slay::~Slay()
	{
	}

	int Slay::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//trigger deal damage event
			unit::StatusContainer* sc = p_info->m_source->getStatusContainer();
			ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::Deal_Damage);
			t->putPackage(INFO_PACKAGE_KEY, p_info);
			sc->triggerTP(ability::TimePointEvent::Deal_Damage, t);

			//deal damaga to all units
			for (unit::Unit* u : p_info->m_targets)
			{
				//trigger receive damage event
				sc = u->getStatusContainer();
				t = new ability::TimePointEvent(ability::TimePointEvent::Receive_Damage);

				//get copy of package
				AbilityInfoPackage* clonePackage = new AbilityInfoPackage(*p_info);
				t->putPackage(INFO_PACKAGE_KEY, clonePackage);
				sc->triggerTP(ability::TimePointEvent::Receive_Damage, t);

				int power = -(clonePackage->m_intValue.find("power")->second);

				damage(u, power);

				//delete clone
				delete clonePackage;
			}
		}

		//delete package
		done(p_info);

		return 0;
	}

}