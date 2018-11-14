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

	TileInfo* info = m_attachedObject->getComponent<TileInfo>();
	if (info->isHighlighted(TileInfo::ForRange))
	{
		e->putInt("highlighted", TRUE);

		kitten::Event::TileList list = BoardManager::getInstance()->getArea();
		e->putInt(TILE_NUMBER, list.size());

		for (int i = 0; i < list.size(); i++)
		{
			int x = list[i].first;
			int z = list[i].second;
			kitten::K_GameObject* tileGO = BoardManager::getInstance()->getTile(x, z);

			std::stringstream stm;
			stm << TILE << i;
			std::string key = stm.str();

			e->putGameObj(key, tileGO);
		}
	}
	else
	{
		e->putInt("highlighted", FALSE);
	}

	BoardManager::getInstance()->getArea();

	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Unhighlight_Tile, nullptr);

	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Tile_Clicked, e);
}

void SendSelfOnClick::onHoverStart()
{
	TileInfo* info = m_attachedObject->getComponent<TileInfo>();
	if (info->isHighlighted(TileInfo::ForRange))
	{
		BoardManager::getInstance()->showArea(m_attachedObject);
	}
}

void SendSelfOnClick::onHoverEnd()
{
}
