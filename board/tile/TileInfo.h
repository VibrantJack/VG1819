#pragma once

#define DEFAULT_OWNER "NONE"

#include "kitten\K_Component.h"
#include "board/tile/landInfo/LandInfoManager.h"
class TileInfo : public kitten::K_Component
{
public:
	TileInfo(int p_iPosX = 0, int p_iPosY = 0);
	~TileInfo();

	//land info
	void setType(LandInformation::TileType p_type = LandInformation::Grassland);
	void start();
	void setRenderTexture();
	int getMVCost();
	const std::string getDescription();
	void effect(ability::TimePointEvent::TPEventType p_tp, unit::Unit* p_u);

	//highlight 
	bool isHighlighted();
	void setHighlighted(bool p_bool);

	//position
	int getPosX();
	void setPosX(int p_int);
	int getPosY();
	void setPosY(int p_int);
	std::pair<int, int> getPos();
	void setPos(int p_x, int p_z);
	void setPos(std::pair<int, int> p_pos);

	//unit on this tile
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

	LandInformation::TileType m_tileType;

	kitten::K_GameObject* m_unitGO;
	LandInformation* m_landInfo;
};