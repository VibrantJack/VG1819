#include "UnitSelect.h"
#include "unit/Unit.h"
#include <iostream>
#include <sstream>

// Networking
#include "networking\ClientGame.h"

unit::UnitSelect::UnitSelect() : m_disableInteraction(false)
{
}

unit::UnitSelect::~UnitSelect()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Pause_Menu_Open, this);
}

void unit::UnitSelect::start()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Pause_Menu_Open,
		this,
		std::bind(&unit::UnitSelect::toggleUnitClickableListener, this, std::placeholders::_1, std::placeholders::_2));
}

void unit::UnitSelect::onClick()
{
	Unit* u = m_attachedObject->getComponent<Unit>();

	// If ClientGame is not nullptr, then we're networking
	// If the player client id doesn't match the unit client id, then they cannot perform actions on the unit
	networking::ClientGame* client = networking::ClientGame::getInstance();
	if (m_disableInteraction)
	{
		return;
	}
	else if (client)
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

void unit::UnitSelect::toggleUnitClickableListener(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_storage->hide();
	bool isEnabled = p_data->getInt(PAUSE_MENU_OPEN);
	m_disableInteraction = isEnabled;
}

