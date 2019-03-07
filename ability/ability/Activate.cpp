#include "ability/ability/Ability.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"

//Rock

namespace ability
{
	int Activate::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			kitten::K_GameObject* target = &p_info->m_targets[0]->getGameObject();
			unit::InitiativeTracker::getInstance()->addExtraTurn(target);
			UniversalSounds::playSound("tambourine");
		}

		done(p_info);

		return 0;
	}
}