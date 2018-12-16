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

	TileInfo* info = m_attachedObject->getComponent<TileInfo>();

	//check if the tile is selected
	if (info->isHighlighted(TileInfo::Select))
	{//check select mode
		if (BoardManager::getInstance()->m_selectRepeat)
		{
			BoardManager::getInstance()->tileClicked(true);
		}
		else
		{
			BoardManager::getInstance()->deselect();
		}
		return;
	}


	if (info->isHighlighted(TileInfo::Range) || info->isHighlighted(TileInfo::Area))
	{
		BoardManager::getInstance()->tileClicked(true);
	}
	else
	{
		BoardManager::getInstance()->tileClicked(false);
	}
}

void SendSelfOnClick::onHoverStart()
{
	TileInfo* info = m_attachedObject->getComponent<TileInfo>();
	if (info->isHighlighted(TileInfo::Range))
	{
		BoardManager::getInstance()->showArea(m_attachedObject);
	}
}

void SendSelfOnClick::onHoverEnd()
{
}
