#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	Move::Move()
	{
	}

	Move::~Move()
	{
	}

	int Move::effect(AbilityInfoPackage* p_info)
	{
		unit::Unit* source = p_info->m_source;

		kitten::K_GameObject* tile = p_info->m_targetTilesGO[0];

		source->move(tile);

		//delete package
		delete p_info;

		return 0;
	}

}