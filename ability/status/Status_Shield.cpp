#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
//Rock

namespace ability
{
	Status_Shield::Status_Shield() : Status::Status()
	{
		m_name = STATUS_SHIELD;
		addTimePoint(TimePointEvent::Receive_Damage);
	}

	int Status_Shield::effect(ability::TimePointEvent::TPEventType p_type, ability::TimePointEvent * p_event)
	{
		if (p_type == ability::TimePointEvent::Receive_Damage)
		{
			AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAbilityInfo);
			AbilityInfoPackage* pack = p_event->getPackage(INFO_PACKAGE_KEY);

			//get amount of sheild
			int shield = m_counter[UNIT_POWER];
			//get damage
			int damage = pack->m_intValue[UNIT_POWER];

			if (damage >= shield)
			{
				int changedValue = -shield;
				node->effect(pack, UNIT_POWER, changedValue);//damage is reduced by shield

				removeThis();//no more shield, remove status
			}
			else
			{
				shield -= damage;//shield reduce amount equal to damage
				int changedValue = -damage;
				node->effect(pack, UNIT_POWER, changedValue);
			}
			
			return 0;
		}
		return 1;
	}
}