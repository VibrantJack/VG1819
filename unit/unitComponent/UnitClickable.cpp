
#include "UnitClickable.h"
#include "unit/UnitCommon.h"
#include "unit/Unit.h"
#include "unit/unitComponent/UnitMove.h"
#include "unit/UnitMonitor.h"
#include "puppy/Text/TextBox.h"
#include "components/SelectAbility.h"
#include "kitten/InputManager.h"
#include <iostream>
#include <sstream>

// Networking
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

	// If ClientGame is not nullptr, then we're networking
	// If the player client id doesn't match the unit client id, then they cannot perform actions on the unit
	networking::ClientGame* client = networking::ClientGame::getInstance();
	if (client)
	{
		if (client->getClientId() != u->m_clientId)
		{
			return;
		}
		// Should have an else here that allows a player to view the clicked units stats even though
		// they cannot click on the unit to perform actions
	}
	
	std::cout << "Player clicked " << u->m_name << std::endl;

	if (u->isTurn())
	{
		m_select = true;
	}
	else
	{
		m_select = false;
	}
	/*
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
	}*/

	//for test
	//u->destroyedByDamage();
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
	//Unit* u = m_attachedObject->getComponent<Unit>();
	//u->useAbility("Fight");
}

void unit::UnitClickable::start()
{
	Clickable::start();
	m_select = false;
	m_set = false;
	counter = 0;
	m_instructionList = new std::vector<std::string>();

	m_message = "";

	addAbility("Turn End");

	Unit* u = m_attachedObject->getComponent<Unit>();
	if (u->m_attributes["base_mv"] > 0)
		addAbility("Move");

	if (u->isCommander())
	{
		addAbility("ManipulateTile");
		addAbility("Summon");
	}

	for (auto it : u->m_ADList)
	{
		addAbility(it.first);
	}

	//for test
	addAbility("For test: Level Up");
	addAbility("For test: Destroy");
}

void unit::UnitClickable::update()
{
	Unit* u = m_attachedObject->getComponent<Unit>();
	if (!m_set && m_select)
	{
		m_textBoxGO->getComponent<puppy::TextBox>()->setText(m_message);
		m_textBoxGO->getComponent<SelectAbility>()->set(u,m_instructionList);
		m_set = true;
		//m_show = false;
	}
	else if(!m_select && m_set)
	{
		m_textBoxGO->getComponent<puppy::TextBox>()->setText("");
		m_set = false;
	}

	if (m_select)
	{
		for (int i = 0; i < m_instructionList->size(); i++)
		{
			char numkey = '0' + i;
			if (input::InputManager::getInstance()->keyDown(numkey))
			{
				std::cout << "Player choose " << i << std::endl;
				m_select = false;
				m_textBoxGO->getComponent<SelectAbility>()->select(i);
				break;
			}
		}
	}
}

void unit::UnitClickable::setTextBox(kitten::K_GameObject * p_tb)
{
	m_textBoxGO = p_tb;
}

void unit::UnitClickable::addAbility(const std::string & p_instructionName)
{
	std::stringstream stm;
	stm << counter << ": " << p_instructionName << " \n ";
	m_message += stm.str();

	m_instructionList->push_back(p_instructionName);
	counter++;
}
