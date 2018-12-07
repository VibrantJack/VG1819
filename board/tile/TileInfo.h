#pragma once

#define DEFAULT_OWNER "NONE"

#define TILE_NUMBER "tile_number"
#define TILE "tile"

#include "kitten\K_Component.h"
#include "board/tile/landInfo/LandInfoManager.h"

class TileInfo : public kitten::K_Component
{
public:
	enum HighlightType//descending order, ex: area highlight will cover range highlight
	{
		Area,
		First = Area,
		None,
		Cursor,
		Range,
		Owned,
		Count = Owned+1
	};

	TileInfo(int p_iPosX = 0, int p_iPosY = 0);
	~TileInfo();

	//land info
	void setType(LandInformation::TileType p_type = LandInformation::Grass_land);
	void start();
	void setLand();

	int getMVCost();
	const std::string getDescription();
	void effect(ability::TimePointEvent::TPEventType p_tp, unit::Unit* p_u);

	//highlight 
	void changeHighlightTexture(const std::string& p_texpath);
	bool isHighlighted(HighlightType p_type);
	void setHighlighted(HighlightType p_type, bool p_bool);
	HighlightType getHighlightType();

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
	const int getOwnerId();
	void setOwnerId(const int p_sId);

	const std::string& getHighlightedBy();
	void setHighlightedBy(const std::string& p_sId);

private:
	std::unordered_map<HighlightType,bool> m_highlightType;
	int m_iPosX, m_iPosY;
	int m_sOwnerId;
	std::string m_sHighlightedBy;
	std::string m_lasttexpath;

	LandInformation::TileType m_tileType;

	kitten::K_GameObject* m_unitGO;
	LandInformation* m_landInfo;
};