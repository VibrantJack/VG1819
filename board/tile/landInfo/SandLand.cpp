#include "board/tile/landInfo/LandInformation.h"
#include "ability/StatusManager.h"

void SandLand::effectOnStart(unit::Unit* p_unit)
{
	//Unit will temporarily -1 IN

	ability::Status* status = ability::StatusManager::getInstance()->findStatus(STATUS_TEMP_CHANGE);

	status->addAttributeChange(UNIT_IN, -1);
	status->addCounter(UNIT_DURATION, 1);

	status->attach(p_unit);
}