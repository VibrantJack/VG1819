
#include "UnitClickable.h"
#include "unit/UnitCommon.h"
#include "unit/Unit.h"
#include "unit/unitComponent/UnitMove.h"
#include "unit/Commander.h"
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
			u->move();
		}
		else if(u->canAct())
		{
			//test command ability
			//static_cast<Commander*>(u)->manipulateTile();
			//static_cast<Commander*>(u)->spawnUnit();
		}
	}
	else
	{
		//show unit info

		//test command ability
		//static_cast<Commander*>(u)->manipulateTile();
		static_cast<Commander*>(u)->spawnUnit();

		//test fight
		//u->useAbility("Fight");
	}

	//for test
	//u->destroyedByDamage();
}

void unit::UnitClickable::onHoverStart()
{
}

void unit::UnitClickable::onHoverEnd()
{
	Unit* u = m_attachedObject->getComponent<Unit>();
	//u->useAbility("Fight");
}
