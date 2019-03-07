#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	void Horror::applyStatus(AbilityInfoPackage * p_info, unit::Unit* p_unit)
	{
		if (!p_unit->getStatusContainer()->getStatus(STATUS_TEMP_CHANGE, m_name))//doesn't have status
		{
			//apply Status_Temp_Change to target
			ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_TEMP_CHANGE);

			//set properties: name, description, source
			//addStatusInfo(se, p_info);

			//mv -1
			int mv = -(p_info->m_intValue[UNIT_POWER]);
			se->addAttributeChange(UNIT_MV, mv);


			std::vector<std::string> intKeys;
			intKeys.push_back(UNIT_DURATION);

			addStatusInfo(se, p_info, intKeys);
			/*
			//get duration
			int dur = p_info->m_intValue[UNIT_DURATION];
			se->addCounter(UNIT_DURATION, dur);*/

			//attach to target
			se->attach(p_unit);
		}

		if (!p_unit->getStatusContainer()->getStatus(STATUS_IN_CHANGE, m_name))//doesn't have status
		{
			//apply Status_IN_Change to target
			ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_IN_CHANGE);

			//set properties: name, description, source
			//addStatusInfo(se, p_info);

			//reduce target IN to 1
			//get target base initiative
			int in = p_unit->m_attributes[UNIT_BASE_IN];
			int deltaIN = -(in - 1); //reduced to 1
			se->addAttributeChange(UNIT_IN, deltaIN);

			//status info
			std::vector<std::string> intKeys;
			intKeys.push_back(UNIT_DURATION);

			addStatusInfo(se, p_info, intKeys);

			//get duration
			//int dur = p_info->m_intValue[UNIT_DURATION];
			//se->addCounter(UNIT_DURATION, dur);

			//attach to target
			se->attach(p_unit);
		}
	}

	int Horror::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//check if unit has this status
			for (unit::Unit* u : p_info->m_targets)
			{
				applyStatus(p_info, u);
			}
		}

		done(p_info);

		return 0;
	}

}