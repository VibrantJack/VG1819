#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	void Dodge::applyStatus(const AbilityInfoPackage * p_info)
	{
		//apply Status_Dodge to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus("Status_Dodge");

		//attach to target
		se->attach(p_info->m_targets[0]);

		//set properties
		se->m_counter["duration"] = p_info->m_intValue.find("duration")->second;

		//TO DO: register event
	}

	void Dodge::stackStatus(const AbilityInfoPackage * p_info)
	{
		ability::Status* se = p_info->m_targets[0]->getStatus("Status_Dodge");

		//reset duration
		se->m_counter["duration"] = p_info->m_intValue.find("duration")->second;
	}

	Dodge::Dodge()
	{
	}

	Dodge::~Dodge()
	{
	}

	int Dodge::effect(const AbilityInfoPackage* p_info)
	{
		//check if unit has this status
		if (p_info->m_targets[0]->getStatus("Status_Dodge"))
			stackStatus(p_info);
		else
			applyStatus(p_info);

		//delete package
		delete p_info;

		return 0;
	}

}