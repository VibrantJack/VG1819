#include "GameModeManager.h"
#include "AreaControl/ControlArea.h"
#include "networking/ClientGame.h"
#include "AttackDefend/DefendArea.h"

GameModeManager* GameModeManager::sm_instance = nullptr;

static const int s_MaxPoint = 100;

void GameModeManager::registerTile(kitten::K_GameObject * p_tileGO, GameModeComponent::TileType p_type)
{
	//get tile info
	TileInfo* info = p_tileGO->getComponent<TileInfo>();
	m_modeComponentMap[p_type]->addTile(info);
}

void GameModeManager::listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	if (p_type == kitten::Event::New_Game_Turn)
	{
		for (auto component : m_modeComponentMap)
		{
			component.second->check();
		}
	}

	checkPoints();
}

void GameModeManager::gainPoint(int p_clientId, int p_points)
{
	if (p_clientId >= 0)
		m_points[p_clientId] += p_points;
}

GameModeManager::GameModeManager()
	:m_points(std::vector<int>({0,0}))
{
	registerEvent();

	init();
}

GameModeManager::~GameModeManager()
{
	deregisterEvent();

	for (auto comp : m_modeComponentMap)
	{
		delete comp.second;
	}
	m_modeComponentMap.clear();
}

void GameModeManager::init()
{
	m_modeComponentMap[GameModeComponent::ControlArea] = new ControlArea();
	m_modeComponentMap[GameModeComponent::DefendArea] = new DefendArea();
}

void GameModeManager::registerEvent()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::New_Game_Turn,
		this,
		std::bind(&GameModeManager::listenEvent, this, std::placeholders::_1, std::placeholders::_2));
}

void GameModeManager::deregisterEvent()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::New_Game_Turn, this);
}

void GameModeManager::checkPoints()
{
	//Note: GameModeManager::checkPoints() check points from clientId 0 to 1
	//if both player reach max points, client 0 always win

	int clientId = -1;
	for (int i = 0; i < m_points.size(); i++)
	{
		if (m_points[i] >= s_MaxPoint)//reach max points
		{
			clientId = i;
			break;
		}
	}

	if (clientId < 0)//no one reach max points
		return;

	if (networking::ClientGame::isNetworkValid())
	{
		networking::ClientGame* client = networking::ClientGame::getInstance();

		kitten::Event* eventData = new kitten::Event(kitten::Event::Network_End_Game);
		if (clientId == client->getClientId())
		{
			eventData->putInt(GAME_END_RESULT, HOST_COMMANDER_DIED);
		}
		else
		{
			eventData->putInt(GAME_END_RESULT, CLIENT_COMMANDER_DIED);
		}

		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Network_End_Game, eventData);
	}
}

