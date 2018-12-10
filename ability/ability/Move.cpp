#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	int Move::effect(AbilityInfoPackage* p_info)
	{
		unit::Unit* source = p_info->m_source;

		//kitten::K_GameObject* tile = p_info->m_targetTilesGO[0];

		source->move(p_info->m_targetTilesGO);

		//delete package
		delete p_info;

		return 0;
	}

}