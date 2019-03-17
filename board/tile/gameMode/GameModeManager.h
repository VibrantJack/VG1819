#pragma once
#include "kitten/K_Common.h"
#include <assert.h>
#include "kitten/event_system/EventManager.h"


class GameModeManager
{
public:
	static void createInstance() { assert(sm_instance == nullptr); sm_instance = new GameModeManager(); };
	static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
	static GameModeManager * getInstance() { return sm_instance; };


	void registerTile(kitten::K_GameObject* p_tileGO);
	void listenEvent(kitten::Event::EventType p_type, kitten::Event* p_data);

private:
	static GameModeManager* sm_instance;
	GameModeManager();
	~GameModeManager();

	void registerEvent();
	void deregisterEvent();

	std::vector<kitten::K_GameObject*> tileList;//the list of tile that need to be watched
	int m_point; //the point of current player has
};