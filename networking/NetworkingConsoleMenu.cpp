#include "networking\NetworkingConsoleMenu.h"
#include "kitten\InputManager.h"

#include <iostream>
#include <process.h>

// Networking stuff
#include "networking\ServerGame.h"
#include "networking\ClientGame.h"
#include "networking\NetworkData.h"

NetworkingConsoleMenu::NetworkingConsoleMenu()
	:
	m_bMenuOpen(false),
	m_bPrintText(false),
	m_bClientUpdate(false),
	m_bServerUpdate(false)
{
	// Uncomment for testing on a single machine, then enable client instance through menu
	/*networking::ServerGame::createInstance();
	if (networking::ServerGame::getInstance()->setupNetwork())
	{
		_beginthread(serverLoop, 0, (void*)12);
	} else
	{
		networking::ServerGame::destroyInstance();
	}*/
}

NetworkingConsoleMenu::~NetworkingConsoleMenu()
{
	if (m_bClientUpdate)
	{
		networking::ClientGame::destroyInstance();
	}

	if (m_bServerUpdate)
	{
		networking::ServerGame::destroyInstance();
	}
}

void NetworkingConsoleMenu::update()
{
	if (input::InputManager::getInstance()->keyDown('`') && !input::InputManager::getInstance()->keyDownLast('`'))
	{
		m_bMenuOpen = true;
		m_bPrintText = true;
	}

	if (m_bMenuOpen)
	{
		if (m_bPrintText)
		{
			printf("** Networking Console Menu Opened **");
			printf("7 - Host Game\n");
			printf("8 - Connect to host\n");
			printf("9 - Exit menu\n");
			m_bPrintText = false;
		}

		if (input::InputManager::getInstance()->keyDown('7') && !input::InputManager::getInstance()->keyDownLast('7'))
		{
			networking::ServerGame::createInstance();
			if (networking::ServerGame::getInstance()->setupNetwork())
			{
				m_bClientUpdate = true;				
			} 
			else
			{
				networking::ServerGame::destroyInstance();
			}

			m_bMenuOpen = false;
		}

		if (input::InputManager::getInstance()->keyDown('8') && !input::InputManager::getInstance()->keyDownLast('8'))
		{
			networking::ClientGame::createInstance();

			printf("Enter an address: ");
			std::string addr;
			std::cin >> addr;

			if (networking::ClientGame::getInstance()->setupNetwork(addr))
			{
				m_bClientUpdate = true;
			}
			else
			{
				networking::ClientGame::destroyInstance();
			}

			m_bMenuOpen = false;
		}

		if (input::InputManager::getInstance()->keyDown('9') && !input::InputManager::getInstance()->keyDownLast('9'))
		{
			printf("** Networking Console Menu Closed **");
			m_bMenuOpen = false;
		}
	}

	if (m_bClientUpdate)
	{
		networking::ClientGame::getInstance()->update();
	}

	if (m_bServerUpdate)
	{
		networking::ServerGame::getInstance()->update();
	}
}

void serverLoop(void* arg)
{
	while (true)
	{
		networking::ServerGame::getInstance()->update();
	}
}