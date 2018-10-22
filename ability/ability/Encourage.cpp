#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	void Encourage::applyStatus(const AbilityInfoPackage* p_info)
	{
		//apply Status_Encourage to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus("Status_Encourage");

		//attach to target
		se->attach(p_info->m_targets[0]);

		//set properties
		se->m_counter["duration"] = p_info->m_intValue.find("duration")->second;
		se->m_counter["power"] = p_info->m_intValue.find("power")->second;

		//TO DO: register event
	}

	void Encourage::stackStatus(const AbilityInfoPackage* p_info)
	{
		ability::Status* se = p_info->m_targets[0]->getStatus("Status_Encourage");

		//reset duration
		se->m_counter["duration"] = p_info->m_intValue.find("duration")->second;
	}

	Encourage::Encourage()
	{
	}

	Encourage::~Encourage()
	{
	}

	int Encourage::effect(const AbilityInfoPackage* p_info)
	{
		//check if unit has this status
		if (p_info->m_targets[0]->getStatus("Status_Encourage"))
			stackStatus(p_info);
		else
			applyStatus(p_info);

		//delete package
		delete p_info;

		return 0;
	}

}