#pragma once

#include <string>
#include <vector>

#define MAP_DIRECTORY "data/map/map/"

namespace kibble
{
	class MapReader
	{
	private:
		MapReader();
		~MapReader();
		static MapReader* sm_instance;

		std::vector<std::string> m_mapList;

		void addMap(const std::string& p_mapName);
	public:
		static void createInstance();
		static void destroyInstance();
		static MapReader* getInstance() { return sm_instance; };

		static void loadAllMap(const std::string& p_masterJsonName);

		std::vector<std::pair<int,int> > getMap(int* p_dimX, int* p_dimZ, int* p_id);
	};
}