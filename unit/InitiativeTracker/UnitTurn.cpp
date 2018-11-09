#include "UnitTurn.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"

unit::UnitTurn::UnitTurn()
{
	act = false;
	move = false;
	m_isEnd = false;
}

unit::UnitTurn::~UnitTurn()
{
}

void unit::UnitTurn::turnStart(kitten::K_GameObject* p_unitObj)
{
	m_isEnd = false;

	m_currentUnit = p_unitObj->getComponent<unit::Unit>();

	m_currentUnit->triggerTP(ability::TimePointEvent::Turn_Start);

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
	m_isEnd = true;
	m_currentUnit->triggerTP(ability::TimePointEvent::Turn_End);

	//in case unit is dead, and this unit is actually next unit
	if (m_isEnd)
	{
		m_currentUnit->turnEnd();
		m_currentUnit = nullptr;

		//call initiative tracker
		InitiativeTracker::getInstance()->unitTurnEnd();
	}
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
