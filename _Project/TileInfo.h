#pragma once

#include "kitten\K_Component.h"

class TileInfo : public kitten::K_Component
{
public:
	TileInfo(int p_iPosX, int p_iPosY);
	~TileInfo();

	bool isHighlighted();
	void setHighlighted(bool p_bool);

	int getPosX();
	void setPosX(int p_int);

	int getPosY();
	void setPosY(int p_int);


private:
	bool m_bHighlighted;
	int m_iPosX, m_iPosY;
};