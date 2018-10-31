
#include "UnitClickable.h"
#include "unit/UnitCommon.h"
#include "unit/Unit.h"
#include "unit/unitComponent/UnitMove.h"
#include "unit/UnitMonitor.h"
#include <iostream>
unit::UnitClickable::UnitClickable()
{
}

unit::UnitClickable::~UnitClickable()
{
}

void unit::UnitClickable::onClick()
{
	Unit* u = m_attachedObject->getComponent<Unit>();
	if (u->isTurn())
	{
		//show avaliable action
		//move only for now
		if(u->canMove())
		{ 
			m_attachedObject->getComponent<UnitMove>()->attempToMove();
		}
		else
		{
			std::cout << "Unit can only move once per turn." << std::endl;
		}
	}
	else
	{
		//show unit info
		
	}
}

void unit::UnitClickable::onHoverStart()
{
	/*test level up 
	Unit* u = m_attachedObject->getComponent<Unit>();
	u->levelup();
	UnitMonitor::getInstanceSafe()->printUnit(u);*/
}

void unit::UnitClickable::onHoverEnd()
{
}
