#include "ability/status/Status.h"
#include "unit/UnitCommon.h"
#include "unit/Unit.h"

void ability::Status_Cursed_Being::applyStatus(unit::Unit * p_u)
{
	//check if target has status
	if (p_u->getStatusContainer()->getStatus(STATUS_VAMPIRIC_CURSE, m_Id))// have status
	{
		return;
	}

	//apply Status_Vampiric_Curse to target
	ability::Status* se = ability::StatusManager::getInstance()->findStatus(STATUS_VAMPIRIC_CURSE);
	Status_Vampiric_Curse* s = static_cast<Status_Vampiric_Curse*>(se);

	s->m_source = m_Id;
	s->changeName(m_stringValue["SVC_name"]);
	s->changeDescription(m_stringValue["SVC_description"]);
	s->addCounter(UNIT_POWER, m_intValue["SVC_power"]);
	s->addCounter(UNIT_DURATION, m_intValue["SVC_duration"]);

	//end at turn start
	s->endEffectAt(TimePointEvent::Turn_Start);

	//set caster
	s->setCaster(m_unit);

	//attach to target
	s->attach(p_u);
}

ability::Status_Cursed_Being::Status_Cursed_Being()
{
	m_Id = STATUS_CURSED_BEING;
	m_statusType = StatusType::Stat_Buff;
	addTimePoint(TimePointEvent::Receive_Damage);
	addTimePoint(TimePointEvent::Deal_Damage);
}

int ability::Status_Cursed_Being::effect(const TimePointEvent::TPEventType& p_type, ability::TimePointEvent* p_event)
{
	if (p_type == TimePointEvent::Receive_Damage)
	{
		unit::Unit* target = p_event->getPackage(INFO_PACKAGE_KEY)->m_source;
		applyStatus(target);
	}
	else if (p_type == TimePointEvent::Deal_Damage)
	{
		for (unit::Unit* target : p_event->getPackage(INFO_PACKAGE_KEY)->m_targets)
		{
			applyStatus(target);
		}
	}
	else
	{
		checkDuration(p_type);
	}
	return 0;
}