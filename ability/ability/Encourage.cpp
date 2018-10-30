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

		//set properties
		int dur = p_info->m_intValue.find("duration")->second;
		int pow = p_info->m_intValue.find("power")->second;

		se->addCounter("duration", dur);
		se->addCounter("power", pow);

		se->addTimePoint(TimePointEvent::Deal_Damage);

		//attach to target
		se->attach(p_info->m_target);
	}

	void Encourage::stackStatus(const AbilityInfoPackage* p_info)
	{
		ability::Status* se = p_info->m_target->getStatusContainer()->getStatus("Status_Encourage");

		//reset duration
		int dur = p_info->m_intValue.find("duration")->second;
		se->addCounter("duration", dur);
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
		if (p_info->m_target->getStatusContainer()->getStatus("Status_Encourage"))
			stackStatus(p_info);
		else
			applyStatus(p_info);
		return 0;
	}

}