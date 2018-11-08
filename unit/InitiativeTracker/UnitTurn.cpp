#include "UnitTurn.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"

void unit::UnitTurn::triggerTurnEvent(bool p_start)
{
	unit::StatusContainer* sc = m_currentUnit->getStatusContainer();

	if (p_start)
	{
		ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::Turn_Start);
		sc->triggerTP(ability::TimePointEvent::Turn_Start, t);
	}
	else
	{
		ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::Turn_End);
		sc->triggerTP(ability::TimePointEvent::Turn_End, t);
	}
}

unit::UnitTurn::UnitTurn()
{
	act = false;
	move = false;
}

unit::UnitTurn::~UnitTurn()
{
}

void unit::UnitTurn::turnStart(kitten::K_GameObject* p_unitObj)
{
	m_currentUnit = p_unitObj->getComponent<unit::Unit>();

	triggerTurnEvent(true);

	m_currentUnit->turnStart(this);

	//if the unit's movement is greater than 0, then it can move this turn
	int mv = m_currentUnit->m_attributes["mv"];
	if (mv > 0)
		move = true;

	//comment for testing
	act = true;
}

void unit::UnitTurn::checkTurn()
{
	//if unit can not move or use ability, its turn automatically end
	if (!act && !move)
	{
		turnEnd();
	}
}

void unit::UnitTurn::turnEnd()
{
	triggerTurnEvent(false);

	m_currentUnit->turnEnd();
	m_currentUnit = nullptr;

	//call initiative tracker
	InitiativeTracker::getInstance()->unitTurnEnd();
}

void unit::UnitTurn::turnReset()
{
	m_currentUnit->turnEnd();
	m_currentUnit = nullptr;
}

bool unit::UnitTurn::isCurrent(kitten::K_GameObject * p_unitObj)
{
	Unit* u = p_unitObj->getComponent<Unit>();
	return u == m_currentUnit;
}

void unit::UnitTurn::unitDestroyed()
{
	m_currentUnit = nullptr;
}
