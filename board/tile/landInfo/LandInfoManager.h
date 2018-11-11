/*@Rock 11.7
This is same as ability manager or status manager.
It contains all land info class. It gives out the reference when needed.
*/

#pragma once
#include "board/tile/landInfo/LandInformation.h"

#include <unordered_map>
#include <assert.h>

class LandInfoManager
{
private:
	std::unordered_map<LandInformation::TileType, LandInformation*> m_map;
	static LandInfoManager* sm_instance;
	LandInfoManager();
	~LandInfoManager();
	void add(LandInformation* p_l);
public:
	static void createInstance() { assert(sm_instance == nullptr); sm_instance = new LandInfoManager(); };
	static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
	static LandInfoManager * getInstance() { return sm_instance; };

	LandInformation * getLand(LandInformation::TileType p_type);
};
