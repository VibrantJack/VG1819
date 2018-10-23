#include "SendSelfOnClick.h"
#include "kitten/event_system/EventManager.h"
#include "board/tile/TileInfo.h"
#include <iostream>
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
		e->putInt("tile_number", 1);
		e->putGameObj("tile0", m_attachedObject);
	}
	else
	{
		e->putInt("highlighted", 0);
	}

	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Tile_Clicked, e);
}

void SendSelfOnClick::onHoverStart()
{	/*
	// for test Range 
	kitten::Event* e = new kitten::Event(kitten::Event::Highlight_Tile);
	e->putString(TILE_OWNER_KEY, "Area.");//highlight because of this unit move
	e->putInt("minRange", 1);
	e->putInt("maxRange", 2);//the range is between 1 and mv attributes
	e->putGameObj("tileAtOrigin", m_attachedObject);
	e->putString("use", "test");
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Highlight_Tile, e);*/
}

void SendSelfOnClick::onHoverEnd()
{
	/*
	//for test Range
	kitten::Event* e = new kitten::Event(kitten::Event::Unhighlight_Tile);
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Unhighlight_Tile, e);*/
}
