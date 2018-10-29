
#include "UnitClickable.h"
#include "unit/UnitCommon.h"
#include "unit/Unit.h"
#include "unit/unitComponent/UnitMove.h"
#include <iostream>

// To access client id
#include "networking\ClientGame.h"

unit::UnitClickable::UnitClickable()
{
}

unit::UnitClickable::~UnitClickable()
{
}

void unit::UnitClickable::onClick()
{
	Unit* u = m_attachedObject->getComponent<Unit>();
	if ((networking::ClientGame::getClientId() == u->m_clientId && networking::ClientGame::getClientId() != -1) 
		|| networking::ClientGame::getClientId() == -1)
	{		
		if (u->isTurn())
		{
			//show avaliable action
			//move only for now
			if (u->canMove())
			{
				m_attachedObject->getComponent<UnitMove>()->attempToMove();
			} else
			{
				std::cout << "Unit can only move once per turn." << std::endl;
			}
		} 
		else
		{
			//show unit info

		}
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
