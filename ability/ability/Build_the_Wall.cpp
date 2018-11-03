#include "ability/ability/Ability.h"
#include "unit/Unit.h"
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

	int Build_the_Wall::effect(const AbilityInfoPackage* p_info)
	{
		AbilityNode* node = AbilityNodeManager::getInstance()->findNode("SpawnUnitNode");

		node->effect(m_wallData);

		return 0;
	}

}