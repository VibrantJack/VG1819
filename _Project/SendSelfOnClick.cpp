#include "SendSelfOnClick.h"
#include "kitten/event_system/EventManager.h"
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
	kitten::Event* e = new kitten::Event(kitten::Event::Tile_Clicked_For_Unit_Move);
	e->putGameObj("tileObj", m_attachedObject);
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Tile_Clicked_For_Unit_Move, e);
}

void SendSelfOnClick::onHoverStart()
{
}

void SendSelfOnClick::onHoverEnd()
{
}
