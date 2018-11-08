#include "Unit.h"
#include "unit/unitComponent/UnitMove.h"
#include "kitten/K_GameObject.h"
#include "unitInteraction/UnitInteractionManager.h"
#include <iostream>

// Networking
#include "networking\ClientGame.h"
//@Rock

namespace unit
{
	Unit::Unit()
	{
		m_commander = nullptr;
		m_turn = nullptr;
		m_statusContainer = new StatusContainer();
		m_statusContainer->m_unit = this;
		m_cdRecorder = new CooldownRecorder();
		m_castTimer = new CastTimer();
	}


	Unit::~Unit()
	{
		delete m_statusContainer;
		delete m_cdRecorder;
		delete m_castTimer;
		for (auto it = m_ADList.begin(); it != m_ADList.end(); it++)
		{
			delete it->second;
		}
		if (isCommander())
		{
			delete m_commander;
		}
	}

	//status
	/*
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
	}*/

	StatusContainer * Unit::getStatusContainer()
	{
		return m_statusContainer;
	}

	void Unit::levelup()
	{
		if (m_attributes["lv"] > 0 && m_attributes["lv"] < 3)
		{
			m_attributes["lv"]++;
			ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::Level_Up);
			t->putInt("lv", m_attributes["lv"]);
			m_statusContainer->triggerTP(ability::TimePointEvent::Level_Up, t);
		}
	}

	void Unit::addCommander(Commander* p_c)
	{
		m_commander = p_c;
		m_commander->init(this);
	}

	bool Unit::isCommander()
	{
		return m_commander != nullptr;
	}

	void Unit::manipulateTile()
	{
		m_commander->manipulateTile();
	}

	void Unit::summonUnit()
	{
		m_commander->spawnUnit();
	}

	//turn
	void Unit::turnStart(UnitTurn * p_t)
	{
		assert(m_turn == nullptr);
		m_turn = p_t;

		m_cdRecorder->reduceCD();//reduce cd at start of turn
		m_castTimer->changeTimer();//reduce ct at start of turn
		if (m_castTimer->isCasting())
		{
			playerSkipTurn();//if it still cast, it skips turn
		}
	}

	bool Unit::canMove()
	{
		if (m_attributes["base_mv"] <= 0)//unit can not move, like structure
			return false;
		else if (m_turn != nullptr)//this is unit's turn and check if it can move
			return m_turn->move;
		return true;
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

	void Unit::playerSkipTurn()
	{
		assert(m_turn != nullptr);
		m_turn->turnEnd();
	}

	kitten::K_GameObject * Unit::getTile()
	{
		return m_attachedObject->getComponent<unit::UnitMove>()->getTile();
	}

	void Unit::move()//move by instruction
	{
		if (!canMove())
			return;

		unit::UnitMove* moveComponet = m_attachedObject->getComponent<unit::UnitMove>();
		moveComponet->attempToMove();
	}

	void Unit::move(int p_min, int p_max)//move by ability with range
	{
		if (!canMove())
			return;

		unit::UnitMove* moveComponet = m_attachedObject->getComponent<unit::UnitMove>();
		moveComponet->attempToMove(p_min, p_max);
	}

	void Unit::move(kitten::K_GameObject * p_tile)//move by ability with fixed target
	{
		if (!canMove())
			return;

		if (networking::ClientGame::getInstance())
		{
			int unitIndex = networking::ClientGame::getInstance()->getUnitGameObjectIndex(m_attachedObject);
			int posX = getTile()->getComponent<TileInfo>()->getPosX();
			int posY = getTile()->getComponent<TileInfo>()->getPosY();

			networking::ClientGame::getInstance()->moveUnit(unitIndex, posX, posY);
		}

		unit::UnitMove* moveComponet = m_attachedObject->getComponent<unit::UnitMove>();
		moveComponet->move(p_tile);
	}

	int Unit::useAbility(const std::string& p_abilityName)
	{
		if (!canAct())
			return -1;

		AbilityDescription* ad;
		bool find = m_ADList.find(p_abilityName) != m_ADList.end();
		if (m_ADList.find(p_abilityName) != m_ADList.end())
		{
			std::cout << "use ability: " << p_abilityName << std::endl;
			ad = m_ADList[p_abilityName];
		}
		else
		{
			std::cout << "Ability: " << p_abilityName << " isn't found" << std::endl;
			return -2;//doesn't have ability
		}

		//non commander unit will check unit's lv
		if (m_attributes["lv"] < ad->m_intValue["lv"] && !isCommander())
		{
			std::cout << p_abilityName << "require lv (" << ad->m_intValue["lv"] << ") " << std::endl;
			std::cout << m_name << " is lv (" << m_attributes["lv"] << ")" << std::endl;
			return -3;//means unit can not use this ability
		}

		//check cd
		if (m_cdRecorder->checkCD(ad) != 0)
		{//it's in cool down
			std::cout << p_abilityName << " is in Cooldown. CD remain:"<<m_cdRecorder->checkCD(ad) << std::endl;
			return -4;
		}

		m_cdRecorder->addCD(ad);
		UnitInteractionManager::getInstance()->request(this, ad);

		return 0;
	}

	void Unit::cancelAbility(AbilityDescription* p_ad)
	{
		m_cdRecorder->cancelCD(p_ad);
	}

	void Unit::setCast(AbilityDescription * p_ad, ability::AbilityInfoPackage * p_pack)
	{
		std::string name = p_ad->m_stringValue["name"];
		int time = p_ad->m_intValue["ct"];
		m_castTimer->set(name,p_pack,time);
		playerSkipTurn();
	}

	void Unit::cancelCast()
	{
		m_castTimer->cancelCast();
	}

	int Unit::destroyedByDamage()
	{
		//send destroyed event
		std::cout << m_name << " is destroyed! " << std::endl;
		InitiativeTracker::getInstance()->removeUnit(m_attachedObject);
		return 0;
	}
}
