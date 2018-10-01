#pragma once
#include "ability/node/AbilityNode.h"
#include "Unit/UnitSpawn.h"

//Rock

namespace ability
{
	SpawnUnitNode::SpawnUnitNode()
	{
	}

	int SpawnUnitNode::effect(unit::UnitData* p_data)
	{
		unit::UnitSpawn::getInstance()->spawnUnitObject(p_data);

		return 0;
	}

}