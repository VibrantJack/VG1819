#include "ability/ability/Ability.h"

//Rock

namespace ability
{
	Encourage::Encourage()
	{
	}

	int Encourage::effect(const AbilityInfoPackage* p_info)
	{
		//apply Status_Encourage to target

		ability::Status_Encourage* se = new ability::Status_Encourage();

		//attach to target
		se->attach(p_info->m_target);

		//set properties
		se->m_counter["duration"] = p_info->m_intValue.find("duration")->second;
		se->m_counter["power"] = p_info->m_intValue.find("power")->second;

		//TO DO: register event

		return 0;
	}

}