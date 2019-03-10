#include "ability/status/Status.h"
#include "ability/AbilityMacro.h"
#include "unit/UnitCommon.h"
#include "unit/UnitSpawn.h"
#include "unit/unitComponent/UnitMove.h"
#include "networking/ClientGame.h"

ability::Status_Attach::Status_Attach()
{
	m_Id = STATUS_ATTACH;
	addTimePoint(TimePointEvent::Unit_Destroy);
}

int ability::Status_Attach::effect()
{
	AbilityNode* node = ability::AbilityNodeManager::getInstance()->findNode(ChangeAttribute);
	
	//get power
	int pow = m_intValue[UNIT_POWER];

	if (pow > 0)//positive
	{//change max hp then hp
		node->effect(m_unit, UNIT_MAX_HP, pow);
		node->effect(m_unit, UNIT_HP, pow);
	}
	else//negative
	{
		//change hp then max hp
		node->effect(m_unit, UNIT_HP, pow);
		node->effect(m_unit, UNIT_MAX_HP, pow);
	}
	return 0;
}

int ability::Status_Attach::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event)
{
	if (p_type == TimePointEvent::Unit_Destroy)
	{
		//get lv
		int lv = m_intValue[UNIT_LV];

		if (lv >= 3)
		{
			//summon a new lv2 wraith

			//spawn unit
			kitten::K_GameObject* u = unit::UnitSpawn::getInstance()->spawnUnitObject(m_unitID);
			
			//set tile
			kitten::K_GameObject* tile = m_unit->getTile();
			u->getComponent<unit::UnitMove>()->setTile(tile);

			//set lv
			//u->getComponent<unit::Unit>()->m_attributes[UNIT_LV] = 2;

			//set client id
			if (networking::ClientGame::getInstance() != nullptr)
			{
				u->getComponent<unit::Unit>()->m_clientId = m_intValue[UNIT_ID];
			}
		}
	}
	return 0;
}
