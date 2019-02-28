#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	void Attach::applyStatus(AbilityInfoPackage * p_info, unit::Unit* p_unit)
	{
		//apply Status_Attach to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_ATTACH);

		//get power
		//int pow = p_info->m_intValue[UNIT_POWER];

		//check target is ally or enemy
		int sourceID = p_info->m_source->m_clientId;
		int targetID = p_unit->m_clientId;
		if (sourceID != targetID)//enemy
			p_info->m_intValue[UNIT_POWER] *= -1;

		//add power
		//se->addCounter(UNIT_POWER, pow);
		
		//add lv
		se->m_intValue[UNIT_LV] = p_info->m_source->m_attributes[UNIT_LV];

		//add id
		se->m_intValue[UNIT_ID] = sourceID;


		std::vector<std::string> intKeys;
		intKeys.push_back(UNIT_POWER);

		addStatusInfo(se, p_info, intKeys);

		//attach to target
		se->attach(p_unit);
		
	}

	int Attach::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			unit::Unit* source = p_info->m_source;

			//check if unit has this status
			unit::Unit* u = p_info->m_targets[0];
			if (!u->getStatusContainer()->getStatus(STATUS_ATTACH, m_name))
			{
				applyStatus(p_info, u);
				source->simpleDestroy();
			}
			else//can't act twice, even this doesn't destroy
				source->actDone();
		}

		//delete package
		delete p_info;

		return 0;
	}
}