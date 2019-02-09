#include "board/tile/landInfo/LandInformation.h"
#include "ability/StatusManager.h"

void ForestLand::effectOnStart(unit::Unit* p_unit, TileInfo* p_tInfo)
{
	//Unit will temporarily -1 mv

	ability::Status* status = ability::StatusManager::getInstance()->findStatus(STATUS_TEMP_CHANGE);

	status->changeName(LAND_STATUS_NAME);
	status->changeDescription("MV -1");
	status->addAttributeChange(UNIT_MV, -1);
	status->addCounter(UNIT_DURATION, 1);

	status->attach(p_unit);
}