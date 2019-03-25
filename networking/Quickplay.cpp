#include "Quickplay.h"
#include "kitten\K_GameObjectManager.h"
#include "networking\ClientGame.h"
#include "kitten\K_Instance.h"

Quickplay::Quickplay()
{

}

Quickplay::~Quickplay()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Poll_For_Server, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Quickplay_Find_Game, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Quickplay_Start_Game, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Update_Server_Info, this);
}

void Quickplay::start()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Poll_For_Server,
		this,
		std::bind(&Quickplay::pollForServerListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Quickplay_Find_Game,
		this,
		std::bind(&Quickplay::findGameListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Quickplay_Start_Game,
		this,
		std::bind(&Quickplay::startGameListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Update_Server_Info,
		this,
		std::bind(&Quickplay::setServerInfoListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::K_GameObjectManager* manager = kitten::K_GameObjectManager::getInstance();
	m_serverStatus = manager->createNewGameObject("network_menu/server_status_textbox.json")->getComponent<puppy::TextBox>();
	m_serverStatus->setText("Inactive");

	m_playerCount = manager->createNewGameObject("network_menu/player_count_textbox.json")->getComponent<puppy::TextBox>();
	m_playerCount->setText("");

	m_activeSessions = manager->createNewGameObject("network_menu/active_games_textbox.json")->getComponent<puppy::TextBox>();
	m_activeSessions->setText("");

	kitten::K_GameObject* findGameButtonGO = &getTransform().getChildren()[0]->getAttachedGameObject();
	m_findGameButton = findGameButtonGO->getComponent<userinterface::TriggerEventButton>();
	m_findGameButtonFrame = findGameButtonGO->getComponent<kitten::ClickableFrame>();

	m_loadingScreen = manager->createNewGameObject("UI/loading_screen.json");
	m_loadingScreen->setEnabled(false);

	pollForServer();
}

void Quickplay::update()
{
	if (networking::ClientGame::getInstance() != nullptr && networking::ClientGame::isNetworkValid() && !m_joiningSession)
	{
		networking::ClientGame::getInstance()->update();
	}
}

void Quickplay::pollForServer()
{
	// Try to connect to server
	// Switch to Quickplay screen regardless of connection outcome

	networking::ClientGame* client = networking::ClientGame::getInstance();

	// Check if we've already created an instance of ClientGame
	if (client)
	{
		// Check if we're already polled for a host, then disconnect from it if we have
		if (networking::ClientGame::isNetworkValid())
		{
			client->disconnectFromNetwork();
		}
		client->connectToDedicatedServer();
	} 
	else // If not, get address and create ClientGame instance
	{
		networking::ClientGame::createInstance(networking::ClientGame::getDedicatedServerAddress());
	}

	setServerStatus(networking::ClientGame::isNetworkValid());
}

void Quickplay::pollForServerListener(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	pollForServer();
}

void Quickplay::findGame()
{
	m_loadingScreen->setEnabled(true);
	networking::ClientGame::getInstance()->sendBasicPacket(QUICKPLAY);
}

void Quickplay::findGameListener(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	findGame();
}

void Quickplay::startGame()
{
	m_joiningSession = true;
	kitten::K_Instance::changeScene("mainscene.json");
}

void Quickplay::startGameListener(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	startGame();
}

void Quickplay::setServerInfoListener(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	int updateServerStatus = p_event->getInt(SERVER_STATUS_KEY);
	int updatePlayerCount = p_event->getInt(SERVER_PLAYER_COUNT_KEY);
	int updateActiveSessions = p_event->getInt(SERVER_ACTIVE_SESSIONS_KEY);

	if (updateServerStatus > -1)
	{
		setServerStatus(updateServerStatus);
	}

	if (updatePlayerCount > -1)
	{
		setPlayerCount(updatePlayerCount);
	}

	if (updateActiveSessions > -1)
	{
		setActiveSessions(updateActiveSessions);
	}
}

// 0: Offline, 1: Online, 2: No available sessions
void Quickplay::setServerStatus(int p_status)
{
	switch (p_status)
	{
		case 0:
		{
			m_serverStatus->setText("Offline");
			m_findGameButtonFrame->setEnabled(false);
			m_findGameButton->setActive(false);
			m_playerCount->setText("-");
			m_activeSessions->setText("-");
			break;
		}
		case 1:
		{
			m_serverStatus->setText("Online");
			m_findGameButtonFrame->setEnabled(true);
			m_findGameButton->setActive(true);
			break;
		}
		case 2:
		{
			m_serverStatus->setText("Server Full");
			m_loadingScreen->setEnabled(false);
			break;
		}
		default:
		{
			m_serverStatus->setText("Error");
			m_findGameButtonFrame->setEnabled(false);
			m_findGameButton->setActive(false);
			break;
		}
	}	
}

void Quickplay::setPlayerCount(int p_count)
{
	m_playerCount->setText(std::to_string(p_count));
}

void Quickplay::setActiveSessions(int p_count)
{
	m_activeSessions->setText(std::to_string(p_count));
}