#include "ability/ability/Ability.h"

//Rock

namespace ability
{
	Fight::Fight()
	{
	}

	Fight::~Fight()
	{
	}

	int Fight::effect(const AbilityInfoPackage* p_info)
	{
		//damage target by power
		unit::Unit* target = p_info->m_targets[0];

		//TO DO:send receive damage event to target

		//so power will change to negative
		int power = -(p_info->m_intValue.find("power")->second);

		damage(target,power);

		//delete package
		delete p_info;

		return 0;
	}

}
