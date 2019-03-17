

#pragma once

#include <unordered_map>
#include <string>

#define LAND_DIRECTORY "data/map/land/"

namespace kibble
{
	class LandLoader
	{
	private:
		void createLandInfo(const std::string& p_JsonName);
	public:
		LandLoader();
		~LandLoader();

		void loadAllLand(const std::string& p_masterJsonName);
	};
}