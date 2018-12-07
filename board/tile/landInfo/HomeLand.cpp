#include "board/tile/landInfo/LandInformation.h"
#include "ability/StatusManager.h"
#include "board/tile/TileInfo.h"
void HomeLand::effectOnStay(unit::Unit * p_unit, TileInfo* p_tInfo)
{
	if (p_tInfo->getOwnerId() != p_unit->m_clientId)//not ally
		return;

	//Unit will temporarily +1 mv

	ability::Status* status = ability::StatusManager::getInstance()->findStatus(STATUS_TEMP_CHANGE);

	status->m_source = "Homeland";
	status->addAttributeChange(UNIT_MV, 1);
	status->addCounter(UNIT_DURATION, 1);

	status->attach(p_unit);

	//Unit will reduce income damage by 1
	status = ability::StatusManager::getInstance()->findStatus(STATUS_BLOCK);
	
	status->m_source = "Homeland";
	status->addCounter(UNIT_POWER, 1);

	status->attach(p_unit);
}

void HomeLand::effectOnLeave(unit::Unit * p_unit, TileInfo* p_tInfo)
{
	unit::StatusContainer* sc = p_unit->getStatusContainer();
	ability::Status* status = sc->getStatus(STATUS_BLOCK,"Homeland");
	sc->removeStatus(status);
}