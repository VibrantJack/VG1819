/*
@Rock 12.27
This class will be a component of tile object
It will contain a list of decoration game object to make this tile interesting
*/

#pragma once
#include "board/tile/landInfo/LandInformation.h"

#define MAX_DECO_NUM 3;

class DecorationGenerator
{
public:
	static std::vector<kitten::K_GameObject*> generateDecoration(LandInformation::TileType p_type);

private:
	static void generateGrassDecoration();
};