#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_GameObject.h"
#include "kitten\event_system\EventManager.h"
#include "board/component/Range.h"
#include "board/tile/landInfo/LandInformation.h"
#include <vector>
#include <array>

class BoardCreator : public kitten::K_Component
{
private:
	int m_x;
	int m_z;
	kitten::Event::TileList m_spawnPointList;
	bool m_attachPowerTracker, m_createSimpleTiles;
public:
	BoardCreator();
	~BoardCreator();

	virtual void start() override;

	void setDimension(int x, int z);
	void enablePowerTracker(bool p_enable) { m_attachPowerTracker = p_enable; }
	void enableSimpleTiles(bool p_enable) { m_createSimpleTiles = p_enable; }

private:

	kitten::K_GameObject* createTile(int x, int z, LandInformation::TileType p_type = LandInformation::Grass_land);
	kitten::K_GameObject* createSimpleTile(int x, int z, LandInformation::TileType p_type = LandInformation::Grass_land);
};