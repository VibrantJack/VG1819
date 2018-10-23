#include "Unit.h"
#include "unit/unitComponent/UnitMove.h"
#include "kitten/K_GameObject.h"
#include "unitInteraction/UnitInteractionManager.h"
#include <iostream>
//@Rock

namespace unit
{
	Unit::Unit()
	{
		m_turn = nullptr;
		m_statusContainer = new StatusContainer();
	}


	Unit::~Unit()
	{
		delete m_statusContainer;
		for (auto it = m_ADList.begin(); it != m_ADList.end(); it++)
		{
			delete it->second;
		}
	}

	//status
	void Unit::addStatus(ability::Status *p_newStatus)
	{
		m_statusContainer->addStatus(p_newStatus);
	}

	bool Unit::removeStatus(ability::Status * p_oldStatus)
	{
		return m_statusContainer->removeStatus(p_oldStatus);
	}

	ability::Status* Unit::getStatus(const std::string & p_name)
	{
		return m_statusContainer->getStatus(p_name);
	}

	StatusContainer * Unit::getStatusContainer()
	{
		return m_statusContainer;
	}

	//turn
	void Unit::turnStart(UnitTurn * p_t)
	{
		assert(m_turn == nullptr);
		m_turn = p_t;
	}

	bool Unit::canMove()
	{
		assert(m_turn != nullptr);
		return m_turn->move;
	}

	bool Unit::canAct()
	{
		assert(m_turn != nullptr);
		return m_turn->act;
	}

	void Unit::moveDone()
	{
		assert(m_turn != nullptr);
		m_turn->move = false;
		m_turn->checkTurn();
	}

	void Unit::actDone()
	{
		assert(m_turn != nullptr);
		m_turn->act = false;
		m_turn->checkTurn();
	}

	bool Unit::isTurn()
	{
		//if m_turn is nullptr, it means its not this unit turn
		return m_turn != nullptr;
	}

	void Unit::turnEnd()
	{
		assert(m_turn != nullptr);
		m_turn = nullptr;
	}

	kitten::K_GameObject * Unit::getTile()
	{
		return m_attachedObject->getComponent<unit::UnitMove>()->getTile();
	}

	
	int Unit::useAbility(const std::string& p_abilityName)
	{
		AbilityDescription* ad;
		bool find = m_ADList.find(p_abilityName) != m_ADList.end();
		if (m_ADList.find(p_abilityName) != m_ADList.end())
		{
			std::cout << "use ability: " << p_abilityName << std::endl;
			ad = m_ADList[p_abilityName];
		}
		else
		{
			return -1;//doesn't have ability
		}

		//check unit's lv
		if (m_attributes["lv"] < ad->m_intValue["lv"])
		{
			return 1;//means unit can not use this ability
		}

		UnitInteractionManager::getInstance()->request(this, ad);
	}
	/*
	int Unit::callStatus(int p_StatusIndex, int p_event)
	{
		//TO DO: method call for status
		return false;
	}*/

	int Unit::destroyedByDamage()
	{
		//send destroyed event

		InitiativeTracker::getInstance()->removeUnit(m_attachedObject);
		return 0;
	}
}
