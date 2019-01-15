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
	//move camera to current unit
	m_display->displayNewUnitTurn(p_unitObj);

	m_isEnd = false;

	m_currentUnit = p_unitObj->getComponent<unit::Unit>();

	m_currentUnit->triggerTP(ability::TimePointEvent::Turn_Start);

	if (m_currentUnit == nullptr)
		return;

	m_currentUnit->turnStart(this);
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

void unit::UnitTurn::setEnd()
{
	//no unit left, no unit takes turn
	m_currentUnit = nullptr;
	m_isEnd = false;
}

void unit::UnitTurn::setNewTurnDisplay(TurnChangeDisplay * p_display)
{
	m_display = p_display;
}
