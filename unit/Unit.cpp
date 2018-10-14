#include "Unit.h"

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
	void Unit::setTurn(UnitTurn * p_t)
	{
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
		m_turn->turnEnd();
		m_turn = nullptr;
	}

	/*
	int Unit::useAbility(const std::string& p_abilityName)
	{
		AbilityDescription* ad = m_ADList[p_abilityName];

		//check unit's lv
		if (m_attributes["LV"] < ad->m_intValue["LV"])
		{
			return 1;//means unit can not use this ability
		}

		//TO DO: cost counter
		if (ad->m_stringValue.find("counter") != ad->m_stringValue.end())
		{
			//TO DO:ask player to cost counter
			std::string counterName = ad->m_stringValue["counter"];
			int maxNum = m_attributes[counterName];
			//info->m_counterNumber =
		}

		//TO DO: get target, passing range and area
		//display range and area
		//select
		//get target info
		//if targetNum = 0
		//return 2
		
		//TO DO assemble info package

		//test purpose
		ability::AbilityInfoPackage* info = new ability::AbilityInfoPackage();
		info->m_source = this;
		info->m_target = this;

		std::string name = ad->m_stringValue["name"];
		info->m_intValue["power"] = ad->m_intValue["power"];

		return ability::AbilityManager::getInstance()->useAbility(name, info);
	}

	int Unit::callStatus(int p_StatusIndex, int p_event)
	{
		//TO DO: method call for status
		return false;
	}*/

	int Unit::destroyedByDamage()
	{
		//send destroyed event
		//destroy unit (game object)
		InitiativeTracker::getInstance()->removeUnit(m_attachedObject);
		return 0;
	}
}
