
#include "UnitClickable.h"
#include "unit/UnitCommon.h"
#include "unit/Unit.h"
#include "unit/unitComponent/UnitMove.h"
unit::UnitClickable::UnitClickable()
{
}

unit::UnitClickable::~UnitClickable()
{
}

void unit::UnitClickable::onClick()
{
	bool turn = m_attachedObject->getComponent<Unit>()->isTurn();
	if (turn)
	{
		//show avaliable action
		//move only for now
		m_attachedObject->getComponent<UnitMove>()->attempToMove();
	}
	else
	{
		//show unit info
		
	}
}

void unit::UnitClickable::onHoverStart()
{
}

void unit::UnitClickable::onHoverEnd()
{
}
