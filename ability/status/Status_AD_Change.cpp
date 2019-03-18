#include "ability/status/Status.h"
#include "ability/AbilityMacro.h"

ability::Status_AD_Change::Status_AD_Change()
{
	m_Id = STATUS_AD_CHANGE;
	//addTimePoint(TimePointEvent::Turn_End);
	endEffectAt();
}

int ability::Status_AD_Change::effect()
{
	setEffectedAD();

	changeEffectedAD();
	return 0;
}

int ability::Status_AD_Change::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event)
{
	checkDuration(p_type);
	return 1;
}

void ability::Status_AD_Change::effectEnd()
{
	changeEffectedAD(true);
}