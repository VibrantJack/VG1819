#pragma once
#include "InitiativeTracker.h"
#include "unit/Unit.h"
#include "kitten/K_GameObjectManager.h"
#include "unit/InitiativeTracker/InitiativeTrackerUI.h"
#include "kibble/kibble.hpp"
#include <algorithm>

//Rock

unit::InitiativeTracker* unit::InitiativeTracker::sm_instance = nullptr;

void unit::InitiativeTracker::sortListByIn(int p_list)
{
	//sort the unit object list 
	//highest intiative unit go first
	switch (p_list)
	{
	case 1:
		std::sort(m_waitUnitObjectList.begin(), m_waitUnitObjectList.end(), [](kitten::K_GameObject * p_u1, kitten::K_GameObject * p_u2)
		{
			int in1 = p_u1->getComponent<unit::Unit>()->m_attributes["in"];
			int in2 = p_u2->getComponent<unit::Unit>()->m_attributes["in"];
			return in1 > in2;
		});
		break;
	default:
		std::sort(m_unitObjectList.begin(), m_unitObjectList.end(), [](kitten::K_GameObject * p_u1, kitten::K_GameObject * p_u2)
		{
			int in1 = p_u1->getComponent<unit::Unit>()->m_attributes["in"];
			int in2 = p_u2->getComponent<unit::Unit>()->m_attributes["in"];
			return in1 > in2;
		});
	}
	
}

void unit::InitiativeTracker::addWaitList()
{
	if (!m_waitUnitObjectList.empty())
	{
		m_unitObjectList.insert(m_unitObjectList.end(), m_waitUnitObjectList.begin(), m_waitUnitObjectList.end());
		m_waitUnitObjectList.clear();
	}
}

int unit::InitiativeTracker::getUnitObjectIndex(kitten::K_GameObject * p_uGO)
{
	for (auto it = m_unitObjectList.begin();it!=m_unitObjectList.end();it++)
	{//check if the unit is in normal list
		if (*it == p_uGO)
		{
			int index = it - m_unitObjectList.begin();
			return index;
		}
	}
	for (auto it = m_waitUnitObjectList.begin(); it != m_waitUnitObjectList.end(); it++)
	{//check if the unit is in wait list
		if (*it == p_uGO)
		{
			int i = it - m_waitUnitObjectList.begin();
			int index = m_unitObjectList.size() + i;
			return index;
		}
	}
	assert(false);
	return 0;
}

unit::InitiativeTracker::InitiativeTracker()
{
	m_uturn = new unit::UnitTurn();
	m_UI = new unit::InitiativeTrackerUI();
	m_uAura =kibble::getGameObjectDataParserInstance()->getGameObject("unit_aura.json");
	m_uAura->getTransform().setIgnoreParent(false);
	m_currentUnitIndex = -1;//flag, means object list isn't initialize
}

unit::InitiativeTracker::~InitiativeTracker()
{
	delete m_UI;
	delete m_uturn;
}

void unit::InitiativeTracker::addUnit(kitten::K_GameObject * p_unit)
{
	if (m_currentUnitIndex < 0)//not initialize
	{
		m_unitObjectList.push_back(p_unit);
	}
	else
	{
		m_waitUnitObjectList.push_back(p_unit);
		sortListByIn(1);
		m_UI->change(getUnitObjectIndex(p_unit));
	}

	/*
	m_unitObjectList.push_back(p_unit);
	if (m_currentUnitIndex >= 0)
	{
		int in1 = m_unitObjectList[m_currentUnitIndex]->getComponent<unit::Unit>()->m_attributes["in"];
		int in2 = p_unit->getComponent<unit::Unit>()->m_attributes["in"];
		if (in2 > in1)//new unit at front of current unit
		{
			m_currentUnitIndex++;
		}
		else//new unit at back of current unit
		{
			m_currentUnitIndex--;
		}
		//sort list
		sortListByIn();
	}*/
}

bool unit::InitiativeTracker::removeUnit(kitten::K_GameObject * p_unit)
{
	bool found = false;
	int index;
	for (auto it = m_unitObjectList.begin(); it != m_unitObjectList.end(); it++)
	{
		if (*it == p_unit)
		{
			found = true;
			//get index
			index = it - m_unitObjectList.begin();

			//remove it from list
			m_unitObjectList.erase(it);
			break;
		}
	}

	if (!found)
	{
		for (auto it = m_waitUnitObjectList.begin(); it != m_waitUnitObjectList.end(); it++)
		{//check if the unit is in wait list
			if (*it == p_unit)
			{
				found = true;
				//get index
				int i = it - m_waitUnitObjectList.begin();
				index = m_unitObjectList.size() + i;

				//remove it from list
				m_waitUnitObjectList.erase(it);
				break;
			}
		}
	}

	if (found)
	{
		m_UI->change(index);

		//pass turn to next
		if (m_uturn->isCurrent(p_unit))
		{
			m_uturn->unitDestroyed();
			if (m_currentUnitIndex < getUnitNumber()) // there is next unit
				m_uturn->turnStart(getCurrentUnit());
			else if (getUnitNumber() > 0)//there's unit but not this
				gameTurnStart();//start a new turn
			else//no unit left
				m_uturn->setEnd();
		}

		kitten::K_GameObjectManager::getInstance()->destroyGameObject(p_unit);
		return true;
	}

	assert(false);//not found
	return false;
}

kitten::K_GameObject * unit::InitiativeTracker::getUnitByIndex(int p_index)
{
	if (p_index >= 0 && p_index < m_unitObjectList.size())
	{
		return m_unitObjectList[p_index];
	}
	else
	{
		int index = p_index - m_unitObjectList.size();
		return m_waitUnitObjectList[index];
	}
}

int unit::InitiativeTracker::getUnitNumber()
{
	return m_unitObjectList.size()+m_waitUnitObjectList.size();
}

kitten::K_GameObject * unit::InitiativeTracker::getCurrentUnit()
{
	return getUnitByIndex(m_currentUnitIndex);
}

int unit::InitiativeTracker::getCurrentUnitIndex()
{
	return m_currentUnitIndex;
}

std::vector<kitten::K_GameObject*> unit::InitiativeTracker::getUnitList()
{
	return m_unitObjectList;
}

void unit::InitiativeTracker::gameTurnStart()
{/*
	// TEMPORARY
	// When dynamically adding a new unit, need to reset the turn of the
	// previously current unit
	// Will need a better solution to dynamically adding new units in the middle of a turn
	// instead of just calling gameTurnStart when one is added
	if (m_uturn->move || m_uturn->act)
	{
		m_uturn->turnReset();
	}
	*/

	addWaitList();
	//sort the unit object list
	sortListByIn();

	m_currentUnitIndex = 0;
	m_UI->turnStart();

	if (getUnitNumber() > 0)
	{
		m_uAura->getTransform().setParent(&getCurrentUnit()->getTransform());
		m_uturn->turnStart(getCurrentUnit());//let the unit start its turn
	}
}

void unit::InitiativeTracker::unitTurnEnd()
{
	m_currentUnitIndex++;//iterator point next unit
	if (m_currentUnitIndex < getUnitNumber())
	{
		m_uAura->getTransform().setParent(&getCurrentUnit()->getTransform());
		m_uturn->turnStart(getCurrentUnit());//let next unit start its turn
		m_UI->next();
	}
	else// start a new game turn
	{
		gameTurnEnd();
	}
}

void unit::InitiativeTracker::gameTurnEnd()
{
	//start of new turn
	gameTurnStart();
}
