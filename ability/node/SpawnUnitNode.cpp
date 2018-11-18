#pragma once
#include "ability/node/AbilityNode.h"
#include "Unit/UnitSpawn.h"

//Rock


namespace ability
{
	SpawnUnitNode::SpawnUnitNode()
	{
	}

	kitten::K_GameObject* SpawnUnitNode::spawn(unit::UnitData* p_data)
	{
		kitten::K_GameObject* u = unit::UnitSpawn::getInstance()->spawnUnitObject(p_data);

		return u;
	}

}