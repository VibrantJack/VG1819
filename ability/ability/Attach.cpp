#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
//Rock

namespace ability
{
	void Attach::applyStatus(AbilityInfoPackage * p_info, unit::Unit* p_unit)
	{
		StatusManager* sm = ability::StatusManager::getInstance();

		//apply Status_Attach to target
		ability::Status* se = sm->findStatus(STATUS_ATTACH);

		//check target is ally or enemy
		unit::Unit* source = p_info->m_source;
		int sourceID = source->m_clientId;
		int targetID = p_unit->m_clientId;
		if (sourceID != targetID)//enemy
			p_info->m_intValue[UNIT_POWER] *= -1;

		std::vector<std::string> intKeys;
		intKeys.push_back(UNIT_POWER);

		addStatusInfo(se, p_info, intKeys);

		//attach to target
		se->attach(p_unit);


		//apply status_last_word_summon to target, which will summon a lv1 wraith
		if (source->m_attributes[UNIT_LV] >= 3)
		{
			//check if unit has last word status
			if (p_unit->getStatusContainer()->getStatus(STATUS_LAST_WORD_SUMMON))//has status, can't apply again
				return;

			Status_Last_Word_Summon* s = static_cast<Status_Last_Word_Summon*>(sm->findStatus(STATUS_LAST_WORD_SUMMON));

			//set unit to summon,default level is 1
			s->setUnitToSummon(source->m_kibbleID);

			//add id
			s->m_intValue[CLIENT_ID] = sourceID;

			//add info
			addStatusInfo(s, p_info);

			//attach to target
			s->attach(p_unit);
		}
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

		UniversalSounds::playSound("attach");

		//delete package
		delete p_info;

		return 0;
	}
}