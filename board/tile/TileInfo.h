#pragma once

#define DEFAULT_OWNER = "NONE"

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

	std::pair<int, int> getPos();
	void setPos(std::pair<int, int> p_pos);

	bool hasUnit();
	void setUnit(kitten::K_GameObject* p_u);
	void removeUnit();
	kitten::K_GameObject* getUnit();

	// TODO: Change according to finalized unit id structure
	const std::string& getOwnerId();
	void setOwnerId(const std::string& p_sId);

	const std::string& getHighlightedBy();
	void setHighlightedBy(const std::string& p_sId);

private:
	bool m_bHighlighted;
	int m_iPosX, m_iPosY;
	std::string m_sOwnerId;
	std::string m_sHighlightedBy;
	kitten::K_GameObject* m_unitGO;
};