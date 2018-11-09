#include "ability/ability/Ability.h"
#include "unit/Unit.h"
#include "board/tile/TileInfo.h"
#include <iostream>
//Rock

namespace ability
{
	int Blast::effect(AbilityInfoPackage* p_info)
	{
		std::cout << "Blast Effect" << std::endl;

		getTarget(p_info);

		//trigger deal damage event
		triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

		for (unit::Unit* u : p_info->m_targets)
		{
			//get copy of package
			AbilityInfoPackage* clonePackage = new AbilityInfoPackage(*p_info);

			//trigger receive damage
			triggerTPEvent(ability::TimePointEvent::Receive_Damage, u, clonePackage);

			int power = -(clonePackage->m_intValue.find(UNIT_POWER)->second);

			damage(u, power);

			//delete clone
			delete clonePackage;
		}

		//delete package
		done(p_info);

		return 0;
	}

}
