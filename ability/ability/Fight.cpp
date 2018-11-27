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
		singleTargetDamage(p_info);

		return 0;
	}

}
