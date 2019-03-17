/*@Rock 11.7
Changed from Austin's TileInformationComponent.
This type of components handles the fixed data of land and its effect
It will be part of tile info
*/

#pragma once
#include "kitten/K_Common.h"
#include "unit/Unit.h"

#define LAND_STATUS_NAME "Land Effect"

class TileInfo;
class LandInformation
{
public:
	//========================================================
	//New types will be added here later
	enum TileType {
		Unknown = 0,
		Grass_land,
		Swamp_land,
		Sand_land,
		Forest_land,
		Garden_land,
		Water_land,

		//special land, change by abilities
		Home_land,

		//game mode related tile
		Domain_land,
		Control_land
	};
	//========================================================

	LandInformation(TileType p_Type, const std::string& p_TexturePath, int p_mvCost, const std::string& p_description);
	~LandInformation() { };

	virtual TileType GetType()
	{
		return m_Type;
	};

	virtual const std::string getTexturePath()
	{
		return m_TexturePath;
	}

	virtual int getMVCost()
	{
		return m_mvCost;
	}

	virtual const std::string getDescription()
	{
		return m_description;
	}

	virtual void effectOnPass(unit::Unit* p_unit, TileInfo* p_tInfo) { };
	//will be triggered when unit enter this tile

	virtual void effectOnStay(unit::Unit* p_unit, TileInfo* p_tInfo) { };
	//will be triggered when unit that's on this tile ends its turn

	virtual void effectOnStart(unit::Unit* p_unit, TileInfo* p_tInfo) { };
	//will be triggered when unit that's on this tile starts its turn

	virtual void effectOnLeave(unit::Unit* p_unit, TileInfo* p_tInfo) {};
protected:
	const TileType m_Type;
	const std::string m_TexturePath;
	const int m_mvCost;
	const std::string m_description;
};

class GrassLand : public LandInformation
{
public:
	GrassLand(TileType p_Type, const std::string& p_TexturePath, int p_mvCost, const std::string& p_description) :
		LandInformation(p_Type, p_TexturePath, p_mvCost, p_description) {};
};

class SwampLand : public LandInformation
{
public:
	SwampLand(TileType p_Type, const std::string& p_TexturePath, int p_mvCost, const std::string& p_description) :
		LandInformation(p_Type, p_TexturePath, p_mvCost, p_description) {};

	void effectOnStay(unit::Unit* p_unit, TileInfo* p_tInfo) override;
};

class SandLand : public LandInformation
{
public:
	SandLand(TileType p_Type, const std::string& p_TexturePath, int p_mvCost, const std::string& p_description) :
		LandInformation(p_Type, p_TexturePath, p_mvCost, p_description) {};

	void effectOnStay(unit::Unit* p_unit, TileInfo* p_tInfo) override;
};

class ForestLand : public LandInformation
{
public:
	ForestLand(TileType p_Type, const std::string& p_TexturePath, int p_mvCost, const std::string& p_description) :
		LandInformation(p_Type, p_TexturePath, p_mvCost, p_description) {};

	void effectOnStart(unit::Unit* p_unit, TileInfo* p_tInfo) override;
};

class GardenLand : public LandInformation
{
public:
	GardenLand(TileType p_Type, const std::string& p_TexturePath, int p_mvCost, const std::string& p_description) :
		LandInformation(p_Type, p_TexturePath, p_mvCost, p_description) {};

	void effectOnStart(unit::Unit* p_unit, TileInfo* p_tInfo) override;
};

class WaterLand : public LandInformation
{
public:
	WaterLand(TileType p_Type, const std::string& p_TexturePath, int p_mvCost, const std::string& p_description) :
		LandInformation(p_Type, p_TexturePath, p_mvCost, p_description) {};
};

class HomeLand : public LandInformation
{
public:
	HomeLand(TileType p_Type, const std::string& p_TexturePath, int p_mvCost, const std::string& p_description) :
		LandInformation(p_Type, p_TexturePath, p_mvCost, p_description) {};

	void effectOnStay(unit::Unit* p_unit, TileInfo* p_tInfo) override;
	void effectOnLeave(unit::Unit* p_unit, TileInfo* p_tInfo) override;
};