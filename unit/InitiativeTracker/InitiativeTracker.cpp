#pragma once
#include "InitiativeTracker.h"
#include "kitten/K_GameObjectManager.h"
#include "unit/InitiativeTracker/InitiativeTrackerUI.h"
#include <algorithm>

//Rock

unit::InitiativeTracker* unit::InitiativeTracker::sm_instance = nullptr;

void unit::InitiativeTracker::sortListByIn()
{
	//sort the unit object list 
	//highest intiative unit go first
	std::sort(m_unitObjectList.begin(), m_unitObjectList.end(), [](kitten::K_GameObject * p_u1, kitten::K_GameObject * p_u2)
	{
		int in1 = p_u1->getComponent<unit::Unit>()->m_attributes["in"];
		int in2 = p_u2->getComponent<unit::Unit>()->m_attributes["in"];
		return in1 > in2;
	});
}

unit::InitiativeTracker::InitiativeTracker()
{
	m_uturn = new unit::UnitTurn();
	m_UI = new unit::InitiativeTrackerUI();
	m_currentUnitIndex = -1;//flag, means object list isn't initialize
}

unit::InitiativeTracker::~InitiativeTracker()
{
	//(clear does not delete, but these are getting deleted by game object manager on shutdown)
	//m_unitObjectList.clear();
	delete m_UI;
	delete m_uturn;
}

void unit::InitiativeTracker::createInstance()
{
	assert(sm_instance == nullptr);
	sm_instance = new InitiativeTracker();
}

void unit::InitiativeTracker::destroyInstance()
{
	assert(sm_instance != nullptr);
	delete sm_instance;
	sm_instance = nullptr;
}

unit::InitiativeTracker * unit::InitiativeTracker::getInstance()
{
	return sm_instance;
}

void unit::InitiativeTracker::addUnit(kitten::K_GameObject * p_unit)
{
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
	}
}

bool unit::InitiativeTracker::removeUnit(kitten::K_GameObject * p_unit)
{
	for (auto it = m_unitObjectList.begin(); it != m_unitObjectList.end(); ++it)
	{
		if (*it == p_unit)
		{
			m_unitObjectList.erase(it);
			//get index
			int i = it - m_unitObjectList.begin();
			m_UI->change(i);
			kitten::K_GameObjectManager::getInstance()->destroyGameObject(p_unit);
			return true;
		}
	}
	return false;
}

kitten::K_GameObject * unit::InitiativeTracker::getCurrentUnit()
{
	return m_unitObjectList[m_currentUnitIndex];
}

std::vector<kitten::K_GameObject*> unit::InitiativeTracker::getList()
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
	//sort the list
	sortListByIn();

	m_currentUnitIndex = 0;
	m_UI->turnStart();
	m_uturn->turnStart(getCurrentUnit());//let the unit start its turn
}

void unit::InitiativeTracker::unitTurnEnd()
{
	m_currentUnitIndex++;//iterator point next unit
	if (m_currentUnitIndex<m_unitObjectList.size())
	{
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
