#include "LandLoader.h"
#include "json.hpp"
#include "kibble\json\jsonextra.hpp"
#include "board/tile/landInfo/LandInfoManager.h"

namespace kibble
{

	LandLoader::LandLoader()
	{

	}

	LandLoader::~LandLoader() 
	{

	}

	void LandLoader::createLandInfo(const std::string & p_JsonName)
	{
		//get json file
		nlohmann::json file = jsonIn(LAND_DIRECTORY + p_JsonName);

		//type
		int iType = file["type"];
		LandInformation::TileType type = static_cast<LandInformation::TileType>(iType);

		//texture path
		std::string tex = file["texture"];

		//mv cost
		int cost = file["mv_cost"];

		//description
		std::string des = file["description"];

		LandInformation* info;
		switch (type)
		{
		case LandInformation::Grass_land:
			info = new GrassLand(type, tex, cost, des);
			break;
		case LandInformation::Swamp_land:
			info = new SwampLand(type, tex, cost, des);
			break;
		case LandInformation::Sand_land:
			info = new SandLand(type, tex, cost, des);
			break;
		case LandInformation::Forest_land:
			info = new ForestLand(type, tex, cost, des);
			break;
		case LandInformation::Garden_land:
			info = new GardenLand(type, tex, cost, des);
			break;
		case LandInformation::Water_land:
			info = new WaterLand(type, tex, cost, des);
			break;
		case LandInformation::Home_land:
			info = new HomeLand(type, tex, cost, des);
			break;
		default:
			info = new LandInformation(type, tex, cost, des);
			break;
		}

		//add this to land info manager
		LandInfoManager::getInstance()->add(info);
	}

	void LandLoader::loadAllLand(const std::string & p_masterJsonName)
	{
		nlohmann::json masterFile = jsonIn(LAND_DIRECTORY + p_masterJsonName);
		auto found = masterFile.find("files");
		if (found != masterFile.end())
		{
			auto end = masterFile["files"].cend();
			for (auto it = masterFile["files"].cbegin(); it != end; ++it)
			{
				this->createLandInfo(*it);
			}
		}
	}
}
