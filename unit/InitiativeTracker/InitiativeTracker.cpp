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
}

unit::InitiativeTracker::~InitiativeTracker()
{
	m_unitObjectList.clear();
	delete m_UI;
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
}

bool unit::InitiativeTracker::removeUnit(kitten::K_GameObject * p_unit)
{
	for (auto it = m_unitObjectList.begin(); it != m_unitObjectList.end(); ++it)
	{
		if (*it == p_unit)
		{
			m_unitObjectList.erase(it);
			m_UI->remove(*it);
			kitten::K_GameObjectManager::getInstance()->destroyGameObject(p_unit);
			return true;
		}
	}

	return false;
}

kitten::K_GameObject * unit::InitiativeTracker::findUnit()
{
	//TO DO: implement
	return nullptr;
}

std::vector<kitten::K_GameObject*> unit::InitiativeTracker::getList()
{
	return m_unitObjectList;
}

void unit::InitiativeTracker::gameTurnStart()
{
	//sort the list
	sortListByIn();
	m_currentUnitIterator = m_unitObjectList.begin();
	m_UI->turnStart();

	m_uturn->turnStart(*m_currentUnitIterator);//let the unit start its turn

	//call turn start function of unitTurn
	
}

void unit::InitiativeTracker::unitTurnEnd()
{
	//TO DO: may need to send event

	m_currentUnitIterator++;//iterator point next unit
	if (m_currentUnitIterator != m_unitObjectList.end())
	{
		m_uturn->turnStart(*m_currentUnitIterator);//let next unit start its turn
		m_UI->next();
	}
	else// start a new game turn
	{
		gameTurnStart();
	}
}
