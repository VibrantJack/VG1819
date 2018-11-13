#include "ability/ability/Ability.h"
#include "unit/Unit.h"
#include "unit/unitComponent/UnitMove.h"
#include "kibble/databank/databank.hpp"
//Rock

namespace ability
{
	Build_the_Wall::Build_the_Wall()
	{
		m_wallData = kibble::getUnitFromId(5);
	}

	Build_the_Wall::~Build_the_Wall()
	{
	}

	int Build_the_Wall::effect(AbilityInfoPackage* p_info)
	{
		AbilityNode* node = AbilityNodeManager::getInstance()->findNode(SpawnUnit);

		kitten::K_GameObject* u = node->spawn(m_wallData);
		kitten::K_GameObject* tile = p_info->m_targetTilesGO[0];
		u->getComponent<unit::UnitMove>()->setTile(tile);

		//delete package
		done(p_info);

		return 0;
	}

}