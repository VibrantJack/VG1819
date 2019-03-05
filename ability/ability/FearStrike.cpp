#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
#include "board/tile/TileInfo.h"
//Rock

namespace ability
{
	void FearStrike::applyStatus(AbilityInfoPackage * p_info, unit::Unit* p_unit)
	{
		//reduce target IN to 1

		//apply Status_Temp_Change to target
		ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_IN_CHANGE);

		//set properties: name, description, source
		//addStatusInfo(se, p_info);

		//get target base initiative
		int in = p_unit->m_attributes[UNIT_BASE_IN];
		int deltaIN = -(in - 1); //reduced to 1

		//get duration
		//int dur = p_info->m_intValue[UNIT_DURATION];

		se->addAttributeChange(UNIT_IN, deltaIN);
		//se->addCounter(UNIT_DURATION, dur);


		std::vector<std::string> intKeys;
		intKeys.push_back(UNIT_DURATION);

		addStatusInfo(se, p_info, intKeys);

		//attach to target
		se->attach(p_unit);
	}

	int FearStrike::effect(AbilityInfoPackage* p_info)
	{
		if (checkTarget(p_info))
		{
			//demonic restriction: can not apply [Fear]
			if (p_info->m_source->getTile()->getComponent<TileInfo>()->isDemonicPresence())
			{
				//check if unit has this status
				for (unit::Unit* u : p_info->m_targets)
				{
					if (!u->getStatusContainer()->getStatus(STATUS_IN_CHANGE, m_name))//doesn't have status
					{
						applyStatus(p_info, u);
					}
				}
			}

			UniversalSounds::playSound("deep_clang");
		}

		//damage target and delete package
		singleTargetDamage(p_info);

		return 0;
	}

}