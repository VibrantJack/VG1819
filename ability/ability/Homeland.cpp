#pragma once
#include "ability/ability/Ability.h"
#include "board/tile/TileInfo.h"
#include "unit/Unit.h"

//Rock

int ability::Homeland::effect(AbilityInfoPackage * p_info)
{
	for (kitten::K_GameObject* tile : p_info->m_targetTilesGO)
	{
		tile->getComponent<TileInfo>()->setType(LandInformation::Home_land);
	}
	return 0;
}