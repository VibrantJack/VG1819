#include "ability/ability/Ability.h"

//Rock

namespace ability
{
	QuickShoot::QuickShoot()
	{
	}

	int QuickShoot::effect(const AbilityInfoPackage* p_info)
	{
		//deal damaga to all units

		int power = -(p_info->m_intValue.find("power")->second);

		for (unit::Unit* u : p_info->m_multipleTargets)
		{
			damage(u, power);
		}
		return 0;
	}

}