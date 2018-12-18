#include "SendSelfOnClick.h"
#include "kitten/event_system/EventManager.h"
#include "board/tile/TileInfo.h"
#include "board/BoardManager.h"
#include "unit/unitComponent/UnitSelect.h"
#include "unit/UnitSpawn.h"
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
	TileInfo* info = m_attachedObject->getComponent<TileInfo>();
	if (info->hasUnit())
	{
		info->getUnit()->getComponent<unit::UnitSelect>()->onClick();
	}
	else
	{
		unit::UnitSpawn::getInstanceSafe()->getActionButtonStorage()->hide();
	}

	std::cout << "send tile obj" << std::endl;
	//send event when click

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

	// Debug: For SpawnUnitOnKeyPress to summon a unit on a clicked tile
	kitten::Event* tileData = new kitten::Event(kitten::Event::Tile_Clicked_Debug);
	tileData->putInt(TILE_POS_X, info->getPosX());
	tileData->putInt(TILE_POS_Y, info->getPosY());
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Tile_Clicked_Debug, tileData);
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
