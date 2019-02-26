#include "board/tile/landInfo/LandInformation.h"
#include "ability/StatusManager.h"

void GardenLand::effectOnStart(unit::Unit* p_unit, TileInfo* p_tInfo)
{
	//don't effect structure
	bool isStructure = p_unit->checkTag(STRUCTURE);
	bool isMachine = p_unit->checkTag(MACHINE);
	if (isStructure || isMachine)
		return;

	//Unit will temporarily +1 max hp
	ability::Status* status = ability::StatusManager::getInstance()->findStatus(STATUS_TEMP_CHANGE);
	status->changeName(LAND_STATUS_NAME);
	status->changeDescription("MAX HP +1");
	status->addAttributeChange(UNIT_MAX_HP, 1);
	status->addCounter(UNIT_DURATION, 1);
	status->endEffectAt(ability::TimePointEvent::Turn_Start);

	status->attach(p_unit);

	//Unit will +1 hp.
	ability::AbilityNode* node1 = ability::AbilityNodeManager::getInstance()->findNode(ability::ChangeAttribute);

	//change hp
	node1->effect(p_unit, UNIT_HP, 1);
}