

#pragma once

#include <unordered_map>
#include <string>

#define LAND_DIRECTORY "data/map/land/"

namespace kibble
{
	class LandLoader
	{
	private:
		LandLoader();
		~LandLoader();
		static LandLoader* sm_instance;

		void createLandInfo(const std::string& p_JsonName);
	public:
		static void createInstance();
		static void destroyInstance();

		static void loadAllLand(const std::string& p_masterJsonName);
	};
}