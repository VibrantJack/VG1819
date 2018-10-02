#include "TileInfo.h"

TileInfo::TileInfo(int p_iPosX, int p_iPosY)
	:
	m_bHighlighted(false),
	m_iPosX(p_iPosX),
	m_iPosY(p_iPosY),
	m_sOwnerId("NONE"),
	m_sHighlightedBy("NONE")
{

}

TileInfo::~TileInfo()
{

}

bool TileInfo::isHighlighted()
{
	return m_bHighlighted;
}

void TileInfo::setHighlighted(bool p_bool)
{
	m_bHighlighted = p_bool;
}

int TileInfo::getPosX()
{
	return m_iPosX;
}

void TileInfo::setPosX(int p_int)
{
	m_iPosX = p_int;
}

int TileInfo::getPosY()
{
	return m_iPosY;
}

void TileInfo::setPosY(int p_int)
{
	m_iPosY = p_int;
}

const std::string& TileInfo::getOwnerId()
{
	return m_sOwnerId;
}

void TileInfo::setOwnerId(const std::string& p_sId)
{
	m_sOwnerId = p_sId;
}

const std::string& TileInfo::getHighlightedBy()
{
	return m_sHighlightedBy;
}

void TileInfo::setHighlightedBy(const std::string& p_sId)
{
	m_sHighlightedBy = p_sId;
}