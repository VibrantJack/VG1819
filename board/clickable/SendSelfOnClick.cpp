#include "SendSelfOnClick.h"
#include "kitten/event_system/EventManager.h"
#include "board/tile/TileInfo.h"
#include "board/BoardManager.h"
#include "unit/unitComponent/UnitSelect.h"
#include "unit/UnitSpawn.h"
#include <iostream>
#include <sstream>

#include "networking\ClientGame.h"

#define TEXBOX_LENGTH 100

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

	if (m_tileInfoDisplay != nullptr)
	{
		setTileInfoDisplayText();
	}
}

void SendSelfOnClick::onHoverEnd()
{
}

void SendSelfOnClick::setTileInfoDisplayText()
{
	TileInfo* info = m_attachedObject->getComponent<TileInfo>();

	std::string padding;
	std::stringstream debugText;
	std::stringstream currentLine;

	int tilePosX = info->getPosX();
	int tilePosY = info->getPosY();
	currentLine << "Tile Pos: " << tilePosX << ", " << tilePosY;
	getPadding(currentLine.str(), padding);
	debugText << currentLine.str() << padding;
	currentLine.str(std::string());

	int mvCost = info->getMVCost();
	currentLine << "Move Cost: " << mvCost;
	getPadding(currentLine.str(), padding);
	debugText << currentLine.str() << padding;
	currentLine.str(std::string());

	std::string highlightType;
	switch (info->getHighlightType())
	{
	case TileInfo::Area:
		highlightType = "Area";
		break;
	case TileInfo::None:
		highlightType = "None";
		break;
	case TileInfo::Cursor:
		highlightType = "Cursor";
		break;
	case TileInfo::Range:
		highlightType = "Range";
		break;
	case TileInfo::Owned:
		highlightType = "Owned";
		break;
	default:
		highlightType = "Error";
		break;
	}
	currentLine << "Highlight Type: " << highlightType;
	getPadding(currentLine.str(), padding);
	debugText << currentLine.str() << padding;
	currentLine.str(std::string());

	std::string tileType;
	switch (info->getType())
	{
	case LandInformation::Unknown:
		tileType = "Unknown";
		break;
	case LandInformation::Grass_land:
		tileType = "Grass_land";
		break;
	case LandInformation::Swamp_land:
		tileType = "Swamp_land";
		break;
	case LandInformation::Sand_land:
		tileType = "Sand_land";
		break;
	case LandInformation::Forest_land:
		tileType = "Forest_land";
		break;
	case LandInformation::Garden_land:
		tileType = "Garden_land";
		break;
	case LandInformation::Water_land:
		tileType = "Water_land";
		break;
	case LandInformation::Home_land:
		tileType = "Home_land";
		break;
	default:
		tileType = "Error";
		break;
	}
	currentLine << "Tile Type: " << tileType;
	getPadding(currentLine.str(), padding);
	debugText << currentLine.str() << padding;
	currentLine.str(std::string());

	int hasUnit = info->hasUnit();
	currentLine << "Has Unit: " << hasUnit;
	getPadding(currentLine.str(), padding);
	debugText << currentLine.str() << padding;
	currentLine.str(std::string());

	int ownerId = info->getOwnerId();
	currentLine << "Tile Owner ID: " << ownerId;
	getPadding(currentLine.str(), padding);
	debugText << currentLine.str() << padding;
	currentLine.str(std::string());

	m_tileInfoDisplay->setText(debugText.str());
}

void SendSelfOnClick::getPadding(const std::string& p_string, std::string& p_dest)
{
	p_dest = "";
	if (p_string.length() % TEXBOX_LENGTH == 0)
	{
		return;
	}

	std::stringstream padding;
	int reqPadding = TEXBOX_LENGTH - (p_string.length() % TEXBOX_LENGTH);
	for (int i = 0; i < reqPadding; ++i)
	{
		p_dest += " ";
	}
}