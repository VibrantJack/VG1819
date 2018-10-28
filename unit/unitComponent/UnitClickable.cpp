
#include "UnitClickable.h"
#include "unit/UnitCommon.h"
#include "unit/Unit.h"
#include "unit/unitComponent/UnitMove.h"
#include "unit/Commander.h"
#include "puppy/Text/TextBox.h"
#include "components/SelectAbility.h"
#include <iostream>
#include <sstream>
unit::UnitClickable::UnitClickable()
{
}

unit::UnitClickable::~UnitClickable()
{
}

void unit::UnitClickable::onClick()
{
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
}

void unit::UnitClickable::onHoverEnd()
{
	//Unit* u = m_attachedObject->getComponent<Unit>();
	//u->useAbility("Fight");
}

void unit::UnitClickable::start()
{
	Clickable::start();
	//m_show = false;
	m_set = false;
	counter = 0;
	m_instructionList = new std::vector<std::string>();

	m_message = "";

	addAbility("Turn End");

	Unit* u = m_attachedObject->getComponent<Unit>();
	if (u->m_attributes["base_mv"] > 0)
		addAbility("Move");

	for (int i = 0; i < u->m_tags.size(); i++)
	{
		if (u->m_tags[i] == "Commander")
		{
			addAbility("ManipulateTile");
			addAbility("Summon");
			break;
		}
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
	if (u->isTurn() && !m_set)
	{
		m_textBoxGO->getComponent<puppy::TextBox>()->setText(m_message);
		m_textBoxGO->getComponent<SelectAbility>()->set(u,m_instructionList);
		m_set = true;
		//m_show = false;
	}
	else if(!u->isTurn() && m_set)
	{
		m_textBoxGO->getComponent<puppy::TextBox>()->setText("");
		m_set = false;
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
