#include "ability/status/Status.h"
#include "ability/AbilityMacro.h"
ability::Status_Load::Status_Load()
{
	m_Id = STATUS_LOAD;
	//addTimePoint(TimePointEvent::Deal_Damage);
	endEffectAt(TimePointEvent::Deal_Damage);
}

int ability::Status_Load::effect()
{
	setEffectedAD();

	changeEffectedAD();

	return 0;
}

int ability::Status_Load::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event)
{
	checkDuration(p_type);

	return 1;
}

void ability::Status_Load::effectEnd()
{
	changeEffectedAD(true);
}