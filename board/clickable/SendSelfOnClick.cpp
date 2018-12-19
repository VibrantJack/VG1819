#include "SendSelfOnClick.h"
#include "kitten/event_system/EventManager.h"
#include "board/tile/TileInfo.h"
#include "board/BoardManager.h"
#include "unit/unitComponent/UnitSelect.h"
#include "unit/UnitSpawn.h"
#include <iostream>
#include <sstream>

SendSelfOnClick::SendSelfOnClick() : m_isDisabled(false)
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Pause_Menu_Open,
		this,
		std::bind(&SendSelfOnClick::pausedListener, this, std::placeholders::_1, std::placeholders::_2));
}

SendSelfOnClick::~SendSelfOnClick()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Pause_Menu_Open, this);
}

void SendSelfOnClick::onClick()
{
	if (m_isDisabled)
		return;

	TileInfo* info = m_attachedObject->getComponent<TileInfo>();
	if (info->hasUnit())
	{
		info->getUnit()->getComponent<unit::UnitSelect>()->onClick();
	}
	else
	{
		unit::UnitSpawn::getInstance()->getActionButtonStorage()->hide();
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
}

void SendSelfOnClick::onHoverStart()
{
	if (m_isDisabled)
		return;

	TileInfo* info = m_attachedObject->getComponent<TileInfo>();
	if (info->isHighlighted(TileInfo::Range))
	{
		BoardManager::getInstance()->showArea(m_attachedObject);
	}
}

void SendSelfOnClick::onHoverEnd()
{
}

void SendSelfOnClick::pausedListener(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_isDisabled = p_data->getInt(PAUSE_MENU_OPEN);
}