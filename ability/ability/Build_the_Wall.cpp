#include "ability/ability/Ability.h"
#include "unit/UnitSpawn.h"
#include "unit/unitComponent/UnitMove.h"
#include "networking\ClientGame.h"
//Rock

namespace ability
{
	int Build_the_Wall::effect(AbilityInfoPackage* p_info)
	{
		summonToken(p_info, m_unitIndex);

		//delete package
		done(p_info);

		return 0;
	}
}