#include "networking\NetworkingConsoleMenu.h"

#include <iostream>
#include <process.h>

// Networking stuff
#include "networking\ServerGame.h"
#include "networking\ClientGame.h"
#include "networking\NetworkData.h"
#include "unit\InitiativeTracker\InitiativeTracker.h"

NetworkingConsoleMenu::NetworkingConsoleMenu()
	:
	m_inputMan(nullptr),
	m_bMenuOpen(false),
	m_bPrintText(false),
	m_bEnteringAddress(false),
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
	if (networking::ClientGame::getInstance())
	{
		networking::ClientGame::destroyInstance();
	}

	if (networking::ServerGame::getInstance())
	{
		networking::ServerGame::destroyInstance();
	}
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Return_to_Main_Menu, this);
}

void NetworkingConsoleMenu::start()
{
	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);

	// Add Listeners for exiting to Main Menu and disconnecting from network
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Return_to_Main_Menu,
		this,
		std::bind(&NetworkingConsoleMenu::stopHostingListener, this, std::placeholders::_1, std::placeholders::_2));
}

void NetworkingConsoleMenu::start()
{
	m_textBox = m_attachedObject->getComponent<puppy::TextBox>();
	assert(m_textBox != nullptr);

	m_stringInputDisplay = m_attachedObject->getComponent<StringInputDisplay>();
	assert(m_stringInputDisplay != nullptr);

	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);
}

void NetworkingConsoleMenu::update()
{
	if (m_inputMan->keyDown(m_cEnterMenuKey) && !m_inputMan->keyDownLast(m_cEnterMenuKey))
	{
		m_bMenuOpen = true;
		m_bPrintText = true;
	}

	if (m_bMenuOpen)
	{
		if (m_bPrintText)
		{
			printf("\n** Networking Console Menu Opened **\n");
			printf("%c - Host game\n", m_cHostKey);
			printf("%c - Stop hosting game\n", m_cStopHostKey);
			printf("%c - Connect to host\n", m_cConnectKey);
			printf("%c - Disconnect from host\n", m_cDisconnectKey);
			printf("%c - Exit menu\n", m_cExitMenuKey);
			printf("************************************\n\n");
			m_bPrintText = false;
		}

		// Host game option
		if (m_inputMan->keyDown(m_cHostKey) && !m_inputMan->keyDownLast(m_cHostKey))
		{
			printf("Host Game option selected\n");
			
			hostGame();
			m_bMenuOpen = false;
		}

		// Stop hosting option
		if (m_inputMan->keyDown(m_cStopHostKey) && !m_inputMan->keyDownLast(m_cStopHostKey))
		{
			printf("Stop hosting option selected\n");

			stopHosting();
			m_bMenuOpen = false;
		}

		// Connect to host option
		if (m_inputMan->keyDown(m_cConnectKey) && !m_inputMan->keyDownLast(m_cConnectKey))
		{
			if (networking::ClientGame::isNetworkValid())
			{
				printf("[Client: %d]: already connected to host\n", networking::ClientGame::getInstance()->getClientId());
			}
			else
			{
				printf("Connect to host option selected, enter an address: \n");
				m_textBox->setText("Enter IP Address");
				m_inputMan->setPollMode(false);
				m_bEnteringAddress = true;
				m_bMenuOpen = false;
			}
		}

		// Disconnect from host option
		if (m_inputMan->keyDown(m_cDisconnectKey) && !m_inputMan->keyDownLast(m_cDisconnectKey))
		{
			printf("Disconnect from host option selected\n");
			
			disconnectFromHost();
			m_bMenuOpen = false;
		}

		// Exit menu option
		if (m_inputMan->keyDown(m_cExitMenuKey) && !m_inputMan->keyDownLast(m_cExitMenuKey))
		{
			printf("** Networking Console Menu Closed **\n");
			m_bMenuOpen = false;
		}
	}

	if (m_inputMan->keyDown(GLFW_KEY_ENTER) && !m_inputMan->keyDownLast(GLFW_KEY_ENTER) && m_bEnteringAddress)
	{
		std::string address = m_stringInputDisplay->getString();
		printf("Entered address: %s\n", address.c_str());
		connectToHost(address);
		m_bEnteringAddress = false;
		m_inputMan->setPollMode(true);
	}

	// Call updates if ClientGame/ServerGame are initialized
	if (checkClientNetwork())
	{
		networking::ClientGame::getInstance()->update();
	}

	if (checkServerNetwork())
	{
		networking::ServerGame::getInstance()->update();
	}
}

void NetworkingConsoleMenu::stopHostingListener(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	stopHosting();
}

void NetworkingConsoleMenu::hostGame()
{
	// Check to make sure ServerGame and ClientGame are not initialized
	if (!networking::ServerGame::getInstance() && !networking::ClientGame::getInstance())
	{
		networking::ServerGame::createInstance();
		if (checkServerNetwork())
		{
			printf("Server network setup complete\n");

			// Server setup successful, now setup ClientGame
			networking::ClientGame::createInstance();
			checkClientNetwork();
		}
	} else
	{
		printf("Already hosting/connected to a server\n");
	}
	
}

void NetworkingConsoleMenu::stopHosting()
{
	// Host player should be running an instance of ServerGame and ClientGame
	// First, shutdown local ClientGame
	disconnectFromHost(true);

	// Then, shutdown local server, which alerts all connected clients
	if (networking::ServerGame::getInstance())
	{
		if (networking::ServerGame::isNetworkValid())
		{
			printf("Shutting down server\n");
			networking::ServerGame::getInstance()->shutdownNetwork();
			networking::ServerGame::destroyInstance();
		} else
		{
			printf("Server was not initialized\n");
		}
	} else
	{
		printf("ServerGame is not setup\n");
	}
}

void NetworkingConsoleMenu::connectToHost(const std::string& p_strAddress)
{
	networking::ClientGame* client = networking::ClientGame::getInstance();

	// Check if we've already created an instance of ClientGame
	if (client)
	{
		// Check if we're already connected to a host
		if (!networking::ClientGame::isNetworkValid())
		{
			client->setupNetwork(p_strAddress);
		} 
	} 
	else // If not, get address and create ClientGame instance
	{
		networking::ClientGame::createInstance(p_strAddress);
		checkClientNetwork();
	}
}

void NetworkingConsoleMenu::disconnectFromHost(bool p_bServerShutdown)
{
	// If ServerGame exists and disconnectFromHost was not called by Server, then we should not 
	// remove ClientGame. Host should always disconnect via Stop hosting game option
	if (networking::ServerGame::getInstance() && !p_bServerShutdown)
	{
		printf("Host cannot disconnect from host!\n");
	} else if (networking::ClientGame::getInstance())
	{
		// Make sure that ClientGame is connected to something otherwise don't do anything
		if (networking::ClientGame::isNetworkValid())
		{
			printf("[Client: %d] disconnecting from server\n", networking::ClientGame::getInstance()->getClientId());

			networking::ClientGame::getInstance()->disconnectFromNetwork(p_bServerShutdown);
			networking::ClientGame::destroyInstance();
		}
		else
		{
			printf("Client network error; not connected to server\n");
		}
	} else
	{
		printf("ClientGame is not setup\n");
	}
}

bool NetworkingConsoleMenu::checkClientNetwork()
{
	if (networking::ClientGame::getInstance())
	{
		if (networking::ClientGame::isNetworkValid())
		{
			//printf("Client network setup; connected to server\n");
			return true;
		} else
		{
			printf("Client network setup incomplete; please try again\n");
			networking::ClientGame::destroyInstance();
			return false;
		}
	}
	return false;
}

bool NetworkingConsoleMenu::checkServerNetwork()
{
	if (networking::ServerGame::getInstance())
	{
		if (networking::ServerGame::isNetworkValid())
		{
			return true;
		} else
		{
			printf("Server network setup incomplete; please try again\n");
			networking::ServerGame::destroyInstance();
			return false;
		}
	}
	return false;
}

void NetworkingConsoleMenu::setMenuKeys(
	char p_cEnterMenuKey, char p_cExitMenuKey,
	char p_cHostKey, char p_cStopHostKey,
	char p_cConnectKey, char p_cDisconnectKey)
{
	m_cEnterMenuKey = p_cEnterMenuKey;
	m_cHostKey = p_cHostKey;
	m_cStopHostKey = p_cStopHostKey;
	m_cConnectKey = p_cConnectKey;
	m_cDisconnectKey = p_cDisconnectKey;
	m_cExitMenuKey = p_cExitMenuKey;
}

void serverLoop(void* arg)
{
	while (true)
	{
		networking::ServerGame::getInstance()->update();
	}
}