/*@Rock 11.7
Changed from Austin's TileInformationComponent.
This type of components handles the fixed data of land and its effect
It will be part of tile info
*/

#pragma once
#include "kitten/K_Common.h"
#include "unit/Unit.h"

class LandInformation
{
public:
	//========================================================
	//New types will be added here later
	enum TileType {
		Unknown,
		Grassland,
		Swampland,
	};
	//========================================================

	LandInformation() { };
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

	virtual void effectOnPass(unit::Unit* p_unit) { };
	//will be triggered when unit enter this tile

	virtual void effectOnStay(unit::Unit* p_unit) { };
	//will be triggered when unit that's on this tile ends its turn

	virtual void effectOnStart(unit::Unit* p_unit) { };
	//will be triggered when unit that's on this tile starts its turn
protected:
	TileType m_Type = Unknown;
	std::string m_TexturePath = "textures/tiles/MISSING.tga";
	int m_mvCost = 1;
	std::string m_description = "Land Not Found.";
};

class GrassLand : public LandInformation
{
public:
	GrassLand()
	{
		m_Type = Grassland;
		m_TexturePath = "textures/tiles/grassland.tga";
		m_mvCost = 1;
		m_description = "Ordinary land. Nothing special.";
	};
};

class SwampLand : public LandInformation
{
public:
	SwampLand()
	{
		m_Type = Swampland;
		m_TexturePath = "textures/tiles/missing.tga";
		m_mvCost = 2;
		m_description = "It's hard to move cross it. When stay on it, unit will lost 1 HP.";
	};

	void effectOnStay(unit::Unit* p_unit) override;
};