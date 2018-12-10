#include "UnitSelect.h"
#include "unit/Unit.h"
#include <iostream>
#include <sstream>

// Networking
#include "networking\ClientGame.h"

unit::UnitSelect::UnitSelect()
{
}

unit::UnitSelect::~UnitSelect()
{
}

void unit::UnitSelect::start()
{
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
	else
	{
		bool structure = false;
		for (std::string it : u->m_tags)//strucutre can't join to another unit
		{
			if (it == STRUCTURE)
				structure = true;
		}
		if(!structure)
			addAbility("Join");
	}

	for (auto it : u->m_ADList)
	{
		addAbility(it.first);
	}

	//for test
	addAbility("For test: Level Up");
	addAbility("For test: Destroy");
}

void unit::UnitSelect::onClick()
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
}


void unit::UnitSelect::setTextBox(kitten::K_GameObject * p_tb)
{
	m_textBoxGO = p_tb;
}

void unit::UnitSelect::addAbility(const std::string & p_instructionName)
{
	std::stringstream stm;
	stm << counter << ": " << p_instructionName << " \n ";
	m_message += stm.str();

	m_instructionList->push_back(p_instructionName);
	counter++;
}
