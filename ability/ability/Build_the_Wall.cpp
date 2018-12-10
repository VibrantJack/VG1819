#include "ability/ability/Ability.h"
#include "unit/UnitSpawn.h"
#include "unit/unitComponent/UnitMove.h"
//Rock

namespace ability
{
	int Build_the_Wall::effect(AbilityInfoPackage* p_info)
	{
		kitten::K_GameObject* u = unit::UnitSpawn::getInstanceSafe()->spawnUnitObject(m_unitIndex);
		kitten::K_GameObject* tile = p_info->m_targetTilesGO[0];
		u->getComponent<unit::UnitMove>()->setTile(tile);

		//delete package
		done(p_info);

		return 0;
	}
}