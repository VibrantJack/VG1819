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
		m_storage->display(u);
	}
	else
	{
		m_storage->hide();
	}
}

