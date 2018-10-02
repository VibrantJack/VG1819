#include "TileInfo.h"

TileInfo::TileInfo(int p_iPosX, int p_iPosY)
	:
	m_bHighlighted(false),
	m_iPosX(p_iPosX),
	m_iPosY(p_iPosY)
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