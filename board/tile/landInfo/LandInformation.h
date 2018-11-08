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

	TileType GetType()
	{
		return m_Type;
	};

	const std::string getTexturePath()
	{
		return m_TexturePath;
	}

	int getMVCost()
	{
		return m_mvCost;
	}

	const std::string getDescription()
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
	TileType m_Type = Grassland;
	std::string m_TexturePath = "textures/tiles/grassland.tga";
	int m_mvCost = 1;
	std::string m_description = "Ordinary land. Nothing special.";
};

class SwampLand : public LandInformation
{
	TileType m_Type = Swampland;
	std::string m_TexturePath = "textures/tiles/grassland.tga";
	int m_mvCost = 2;
	std::string m_description = "Dirty road. It's hard to move on it.";
};