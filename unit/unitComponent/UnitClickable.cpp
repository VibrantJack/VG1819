
#include "UnitClickable.h"
#include "unit/UnitCommon.h"
#include "unit/Unit.h"
#include "unit/unitComponent/UnitMove.h"
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

	//for test
	u->destroyedByDamage();
}

void unit::UnitClickable::onHoverStart()
{
}

void unit::UnitClickable::onHoverEnd()
{
	Unit* u = m_attachedObject->getComponent<Unit>();
	u->useAbility("Fight");
}
