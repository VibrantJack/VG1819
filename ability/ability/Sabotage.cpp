#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Sabotage::Sabotage()
	{
	}

	Sabotage::~Sabotage()
	{
	}

	int Sabotage::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//damage target by power

			//trigger deal damage event
			unit::StatusContainer* sc = p_info->m_source->getStatusContainer();
			ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::Deal_Damage);
			t->putPackage(INFO_PACKAGE_KEY, p_info);
			sc->triggerTP(ability::TimePointEvent::Deal_Damage, t);

			unit::Unit* target = p_info->m_targets[0];

			for (auto it : target->m_tags)
			{
				if (it == "Structure")
				{
					//trigger deal damage event
					sc = target->getStatusContainer();
					t = new ability::TimePointEvent(ability::TimePointEvent::Receive_Damage);
					t->putPackage(INFO_PACKAGE_KEY, p_info);
					sc->triggerTP(ability::TimePointEvent::Receive_Damage, t);

					int power = -(p_info->m_intValue.find("power")->second);

					damage(target, power);

					return 1;
				}
			}
		}

		//delete package
		done(p_info);
		
		//target isn't structure
		return 0;
	}

}