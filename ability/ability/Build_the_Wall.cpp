#include "ability/ability/Ability.h"
#include "unit/Unit.h"
#include "kibble/kibble.hpp"
#include "unit/unitComponent/UnitMove.h"
//Rock

namespace ability
{
	Build_the_Wall::Build_the_Wall()
	{
		m_wallData = kibble::getUnitDataParserInstance()->getUnit("Wall.txt");
	}

	Build_the_Wall::~Build_the_Wall()
	{
	}

	int Build_the_Wall::effect(const AbilityInfoPackage* p_info)
	{
		AbilityNode* node = AbilityNodeManager::getInstance()->findNode("SpawnUnitNode");

		kitten::K_GameObject* u = node->spawn(m_wallData);
		kitten::K_GameObject* tile = p_info->m_targetTilesGO[0];
		u->getComponent<unit::UnitMove>()->setTile(tile);

		//delete package
		done(p_info);

		return 0;
	}

}