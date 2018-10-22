#include "ability/ability/Ability.h"
#include "unit/Unit.h"
#include "kibble/kibble.hpp"
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

		node->effect(m_wallData);

		//delete package
		delete p_info;

		return 0;
	}

}