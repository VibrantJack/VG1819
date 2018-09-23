#include "ability/ability/Ability.h"

//Rock

namespace ability
{
	Fight::Fight()
	{
	}

	int Fight::effect(const AbilityInfoPackage* p_info)
	{
		//damage target by power
		unit::Unit* target = p_info->m_target;
		//so power will change to negative
		int power = -(p_info->m_intValue.find("power")->second);

		damage(target,power);

		return 0;
	}

}
