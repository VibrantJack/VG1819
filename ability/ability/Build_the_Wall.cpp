#include "ability/ability/Ability.h"
#include "unit/UnitSpawn.h"
#include "unit/unitComponent/UnitMove.h"
#include "networking\ClientGame.h"
//Rock

namespace ability
{
	int Build_the_Wall::effect(AbilityInfoPackage* p_info)
	{
		kitten::K_GameObject* u = unit::UnitSpawn::getInstanceSafe()->spawnUnitObject(m_unitIndex);
		kitten::K_GameObject* tile = p_info->m_targetTilesGO[0];
		u->getComponent<unit::UnitMove>()->setTile(tile);

		if (networking::ClientGame::getInstance() != nullptr)
		{
			u->getComponent<unit::Unit>()->m_clientId = p_info->m_sourceClientId;
		}

		//delete package
		done(p_info);

		return 0;
	}
}