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

		//set properties
		int dur = p_info->m_intValue.find("duration")->second;
		se->addCounter("duration", dur);

		se->addTimePoint(TimePointEvent::Receive_Damage);

		//attach to target
		se->attach(p_info->m_target);
	}

	void Dodge::stackStatus(const AbilityInfoPackage * p_info)
	{
		ability::Status* se = p_info->m_target->getStatusContainer()->getStatus("Status_Dodge");

		//reset duration
		int dur = p_info->m_intValue.find("duration")->second;
		se->addCounter("duration", dur);
	}

	Dodge::Dodge()
	{
	}

	Dodge::~Dodge()
	{
	}

	int Dodge::effect(AbilityInfoPackage* p_info)
	{
		//check if unit has this status
		if (p_info->m_target->getStatusContainer()->getStatus("Status_Dodge"))
			stackStatus(p_info);
		else
			applyStatus(p_info);
		return 0;
	}

}