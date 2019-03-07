

#include "ability/ability/Ability.h"
#include "unit/Unit.h"

int ability::Join::effect(AbilityInfoPackage* p_info)
{
	unit::Unit* source = p_info->m_source;
	unit::Unit* target = p_info->m_targets[0];

	//check if they are same unit and they have same level
	if (source->m_name == target->m_name && 
		source->m_attributes[UNIT_LV] == target->m_attributes[UNIT_LV])
	{
		//target level up
		target->levelup();

		//animate source unit move to there
		kitten::K_GameObject* tile = target->getTile();
		source->moveAnime(tile);

		//then destroy it
		source->destroyedByJoin();

		UniversalSounds::playSound("join");
	}
	else
	{
		UniversalSounds::playSound("cancel");
	}

	//delete package
	delete p_info;

	return 0;
}