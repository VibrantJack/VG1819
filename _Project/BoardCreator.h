#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_GameObject.h"
#include "kitten\event_system\EventManager.h"
#include <vector>
#include <array>

class BoardCreator : public kitten::K_Component
{
public:
	BoardCreator();
	~BoardCreator();

	virtual void start() override;

	void highlightTile(kitten::Event::EventType p_type, kitten::Event* p_data);
	void unhighlightTile(kitten::Event::EventType p_type, kitten::Event* p_data);
private:
	static kitten::K_GameObject* m_pTileList[15][15];

	//static std::vector<kitten::K_GameObject*> m_pTileList;
};