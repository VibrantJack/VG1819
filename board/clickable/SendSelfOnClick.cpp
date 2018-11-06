#include "SendSelfOnClick.h"
#include "kitten/event_system/EventManager.h"
#include "board/tile/TileInfo.h"
#include "board/BoardManager.h"
#include <iostream>
#include <sstream>
SendSelfOnClick::SendSelfOnClick()
{
}

SendSelfOnClick::~SendSelfOnClick()
{
}

void SendSelfOnClick::onClick()
{
	std::cout << "send tile obj" << std::endl;
	//send event when click
	kitten::Event* e = new kitten::Event(kitten::Event::Tile_Clicked);

	bool highlighted = m_attachedObject->getComponent<TileInfo>()->isHighlighted();
	if (highlighted)
	{
		e->putInt("highlighted", 1);

		kitten::Event::TileList list = BoardManager::getInstance()->getArea();
		e->putInt("tile_number", list.size());

		for (int i = 0; i < list.size(); i++)
		{
			int x = list[i].first;
			int z = list[i].second;
			kitten::K_GameObject* tileGO = BoardManager::getInstance()->getTile(x, z);

			std::stringstream stm;
			stm << "tile" << i;
			std::string key = stm.str();

			e->putGameObj(key, tileGO);
		}
	}
	else
	{
		e->putInt("highlighted", 0);
	}

	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Unhighlight_Tile, nullptr);

	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Tile_Clicked, e);
}

void SendSelfOnClick::onHoverStart()
{
	BoardManager::getInstance()->showArea(m_attachedObject);
}

void SendSelfOnClick::onHoverEnd()
{
	//BoardManager::getInstance()->hideArea();
}
