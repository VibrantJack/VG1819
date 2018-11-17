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
public:
	BoardCreator();
	~BoardCreator();

	virtual void start() override;

	void setDimension(int x, int z);

private:

	kitten::K_GameObject* createTile(int x, int z, LandInformation::TileType p_type = LandInformation::Grass_land);
};