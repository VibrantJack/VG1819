#include "DecorationGenerator.h"
#include "kitten/K_GameObjectManager.h"
#include "board/BoardManager.h"
#include "TileInfo.h"

std::vector<kitten::K_GameObject*> DecorationGenerator::generateDecoration(TileInfo* p_info)
{
	LandInformation::TileType type = p_info->getType();

	int x = p_info->getPosX();
	int y = p_info->getPosY();

	switch (type)
	{
	case LandInformation::Grass_land:
		return generateGrassDecoration();
	case LandInformation::Forest_land:
		return generateForestDecoration();
	case LandInformation::Garden_land:
		return generateGardenDecoration();
	case LandInformation::Swamp_land:
		return generateSwampDecoration();
	case LandInformation::Water_land:
		return generateWaterDecoration(x, y);
	case LandInformation::Sand_land:
		return generateSandDecoration(x, y);
	}
	return std::vector<kitten::K_GameObject*>();
}


std::vector<kitten::K_GameObject*> DecorationGenerator::generateGrassDecoration()
{
	std::vector<kitten::K_GameObject*> list;
	/*
	int n = rand() % MAX_DECO_NUM;//number of decoration

	for (int i = 0; i < n; i++)
	{
		kitten::K_GameObject* k;

		float chance = (float) rand() / RAND_MAX;
		if (chance < 0.7)//70% chance it's grass
		{
			k = kitten::K_GameObjectManager::getInstance()->createNewGameObject("Decoration_grass.json");
		}
		else//30% chance it's stone
		{
			k = kitten::K_GameObjectManager::getInstance()->createNewGameObject("Decoration_stone.json");
		}
		
		list.push_back(k);
	}
	*/
	return list;
}

std::vector<kitten::K_GameObject*> DecorationGenerator::generateForestDecoration()
{
	std::vector<kitten::K_GameObject*> list;
	/*
	//always have 1 tree
	kitten::K_GameObject* k = kitten::K_GameObjectManager::getInstance()->createNewGameObject("Decoration_tree.json");
	list.push_back(k);

	//50% chance it will has one more decoration
	float chance = (float)rand() / RAND_MAX;
	if (chance < 0.5)
	{
		kitten::K_GameObject* k3 = kitten::K_GameObjectManager::getInstance()->createNewGameObject("Decoration_stone.json");
		list.push_back(k3);
	}
	*/
	return list;
}

std::vector<kitten::K_GameObject*> DecorationGenerator::generateGardenDecoration()
{
	return std::vector<kitten::K_GameObject*>();
}

std::vector<kitten::K_GameObject*> DecorationGenerator::generateWaterDecoration(int p_posX, int p_posY)
{
	std::vector<kitten::K_GameObject*> list;
	kitten::K_GameObject* k;
	kitten::K_GameObjectManager* gm = kitten::K_GameObjectManager::getInstance();
	//check tile above this
	LandInformation::TileType upType = getTileType(p_posX, p_posY + 1);
	if (upType == LandInformation::Grass_land ||
		upType == LandInformation::Forest_land || 
		upType == LandInformation::Garden_land)
	{
		k = gm->createNewGameObject("TileDecoration/grass_water_edge/grass_water_edge_2.json");
		list.push_back(k);
	}
	else if (upType == LandInformation::Sand_land)
	{
		k = gm->createNewGameObject("TileDecoration/sand_water_edge/sand_water_edge_2.json");
		list.push_back(k);
	}

	//check tile below this
	LandInformation::TileType downType = getTileType(p_posX, p_posY - 1);
	if (downType == LandInformation::Grass_land ||
		downType == LandInformation::Forest_land ||
		downType == LandInformation::Garden_land)
	{
		k = gm->createNewGameObject("TileDecoration/grass_water_edge/grass_water_edge_7.json");
		list.push_back(k);
	}
	else if (downType == LandInformation::Sand_land)
	{
		k = gm->createNewGameObject("TileDecoration/sand_water_edge/sand_water_edge_7.json");
		list.push_back(k);
	}

	//left
	LandInformation::TileType leftType = getTileType(p_posX + 1, p_posY);
	if (leftType == LandInformation::Grass_land ||
		leftType == LandInformation::Forest_land ||
		leftType == LandInformation::Garden_land)
	{
		k = gm->createNewGameObject("TileDecoration/grass_water_edge/grass_water_edge_4.json");
		list.push_back(k);
		//left up corner
		if (upType == LandInformation::Grass_land ||
			upType == LandInformation::Forest_land ||
			upType == LandInformation::Garden_land)
		{
			k = gm->createNewGameObject("TileDecoration/grass_water_edge/grass_water_edge_1.json");
			list.push_back(k);
		}
		//left down corner
		if (downType == LandInformation::Grass_land ||
			downType == LandInformation::Forest_land ||
			downType == LandInformation::Garden_land)
		{
			k = gm->createNewGameObject("TileDecoration/grass_water_edge/grass_water_edge_6.json");
			list.push_back(k);
		}
	}
	else if (leftType == LandInformation::Sand_land)
	{
		k = gm->createNewGameObject("TileDecoration/sand_water_edge/sand_water_edge_4.json");
		list.push_back(k);
		//left up corner
		if (upType == LandInformation::Sand_land)
		{
			k = gm->createNewGameObject("TileDecoration/sand_water_edge/sand_water_edge_1.json");
			list.push_back(k);
		}
		//left down corner
		if (downType == LandInformation::Sand_land)
		{
			k = gm->createNewGameObject("TileDecoration/sand_water_edge/sand_water_edge_6.json");
			list.push_back(k);
		}
	}

	//right
	LandInformation::TileType rightType = getTileType(p_posX - 1, p_posY);
	if (rightType == LandInformation::Grass_land ||
		rightType == LandInformation::Forest_land ||
		rightType == LandInformation::Garden_land)
	{
		k = gm->createNewGameObject("TileDecoration/grass_water_edge/grass_water_edge_5.json");
		list.push_back(k);

		//right up corner
		if (upType == LandInformation::Grass_land ||
			upType == LandInformation::Forest_land ||
			upType == LandInformation::Garden_land)
		{
			k = gm->createNewGameObject("TileDecoration/grass_water_edge/grass_water_edge_3.json");
			list.push_back(k);
		}
		//right down corner
		if (downType == LandInformation::Grass_land ||
			downType == LandInformation::Forest_land ||
			downType == LandInformation::Garden_land)
		{
			k = gm->createNewGameObject("TileDecoration/grass_water_edge/grass_water_edge_8.json");
			list.push_back(k);
		}
	}
	else if (rightType == LandInformation::Sand_land)
	{
		k = gm->createNewGameObject("TileDecoration/sand_water_edge/sand_water_edge_5.json");
		list.push_back(k);
		//right up corner
		if (upType == LandInformation::Sand_land)
		{
			k = gm->createNewGameObject("TileDecoration/sand_water_edge/sand_water_edge_3.json");
			list.push_back(k);
		}
		//right down corner
		if (downType == LandInformation::Sand_land)
		{
			k = gm->createNewGameObject("TileDecoration/sand_water_edge/sand_water_edge_8.json");
			list.push_back(k);
		}
	}

	/*
	//50% chance it will has one decoration
	float chance = (float)rand() / RAND_MAX;
	if (chance < 0.5)
	{
		kitten::K_GameObject* k = kitten::K_GameObjectManager::getInstance()->createNewGameObject("Decoration_water.json");
		list.push_back(k);
	}*/

	return list;
}

std::vector<kitten::K_GameObject*> DecorationGenerator::generateSandDecoration(int p_posX, int p_posY)
{
	std::vector<kitten::K_GameObject*> list;
	kitten::K_GameObject* k;
	kitten::K_GameObjectManager* gm = kitten::K_GameObjectManager::getInstance();
	//check tile above this
	LandInformation::TileType upType = getTileType(p_posX, p_posY + 1);
	if (upType == LandInformation::Grass_land ||
		upType == LandInformation::Forest_land ||
		upType == LandInformation::Garden_land)
	{
		k = gm->createNewGameObject("TileDecoration/grass_sand_edge/grass_sand_edge_2.json");
		list.push_back(k);
	}

	//check tile below this
	LandInformation::TileType downType = getTileType(p_posX, p_posY - 1);
	if (downType == LandInformation::Grass_land ||
		downType == LandInformation::Forest_land ||
		downType == LandInformation::Garden_land)
	{
		k = gm->createNewGameObject("TileDecoration/grass_sand_edge/grass_sand_edge_7.json");
		list.push_back(k);
	}

	//left
	LandInformation::TileType leftType = getTileType(p_posX + 1, p_posY);
	if (leftType == LandInformation::Grass_land ||
		leftType == LandInformation::Forest_land ||
		leftType == LandInformation::Garden_land)
	{
		k = gm->createNewGameObject("TileDecoration/grass_sand_edge/grass_sand_edge_4.json");
		list.push_back(k);
		//left up corner
		if (upType == LandInformation::Grass_land ||
			upType == LandInformation::Forest_land ||
			upType == LandInformation::Garden_land)
		{
			k = gm->createNewGameObject("TileDecoration/grass_sand_edge/grass_sand_edge_1.json");
			list.push_back(k);
		}
		//left down corner
		if (downType == LandInformation::Grass_land ||
			downType == LandInformation::Forest_land ||
			downType == LandInformation::Garden_land)
		{
			k = gm->createNewGameObject("TileDecoration/grass_sand_edge/grass_sand_edge_6.json");
			list.push_back(k);
		}
	}

	//right
	LandInformation::TileType rightType = getTileType(p_posX - 1, p_posY);
	if (rightType == LandInformation::Grass_land ||
		rightType == LandInformation::Forest_land ||
		rightType == LandInformation::Garden_land)
	{
		k = gm->createNewGameObject("TileDecoration/grass_sand_edge/grass_sand_edge_5.json");
		list.push_back(k);

		//right up corner
		if (upType == LandInformation::Grass_land ||
			upType == LandInformation::Forest_land ||
			upType == LandInformation::Garden_land)
		{
			k = gm->createNewGameObject("TileDecoration/grass_sand_edge/grass_sand_edge_3.json");
			list.push_back(k);
		}
		//right down corner
		if (downType == LandInformation::Grass_land ||
			downType == LandInformation::Forest_land ||
			downType == LandInformation::Garden_land)
		{
			k = gm->createNewGameObject("TileDecoration/grass_sand_edge/grass_sand_edge_8.json");
			list.push_back(k);
		}
	}

	return list;
}

std::vector<kitten::K_GameObject*> DecorationGenerator::generateSwampDecoration()
{
	
	std::vector<kitten::K_GameObject*> list;
	/*
	//50% chance it will has one decoration
	float chance = (float)rand() / RAND_MAX;
	if (chance < 0.5)
	{
		kitten::K_GameObject* k = kitten::K_GameObjectManager::getInstance()->createNewGameObject("Decoration_swamp.json");
		list.push_back(k);
	}*/

	return list;
}

LandInformation::TileType DecorationGenerator::getTileType(int p_x, int p_y)
{
	std::pair<int, int> d = BoardManager::getInstance()->getDimension();

	if (p_x >= 0 && p_x < d.first && p_y >= 0 && p_y < d.second)//on the board
	{
		kitten::K_GameObject* t = BoardManager::getInstance()->getTile(p_x, p_y);
		return t->getComponent<TileInfo>()->getType();
	}

	return LandInformation::Unknown;
}
