#include "LandInfoManager.h"

LandInfoManager* LandInfoManager::sm_instance;

LandInfoManager::LandInfoManager()
{
	LandInformation* l;

	l = new GrassLand();
	add(l);

	l = new SwampLand();
	add(l);
}

LandInfoManager::~LandInfoManager()
{
	for (auto it = m_map.begin(); it != m_map.end(); it++)
	{
		delete it->second;
	}
}

void LandInfoManager::add(LandInformation * p_l)
{
	LandInformation::TileType tt = p_l->GetType();
	m_map[tt] = p_l;
}

LandInformation * LandInfoManager::getLand(LandInformation::TileType p_type)
{
	return m_map[p_type];
}
