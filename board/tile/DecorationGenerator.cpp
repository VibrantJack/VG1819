#include "DecorationGenerator.h"
#include "kitten/K_GameObjectManager.h"

std::vector<kitten::K_GameObject*> DecorationGenerator::generateDecoration(LandInformation::TileType p_type)
{
	switch (p_type)
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
		return generateWaterDecoration();
	}
	return std::vector<kitten::K_GameObject*>();
}


std::vector<kitten::K_GameObject*> DecorationGenerator::generateGrassDecoration()
{
	std::vector<kitten::K_GameObject*> list;

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

	return list;
}

std::vector<kitten::K_GameObject*> DecorationGenerator::generateForestDecoration()
{
	std::vector<kitten::K_GameObject*> list;

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

	return list;
}

std::vector<kitten::K_GameObject*> DecorationGenerator::generateGardenDecoration()
{
	return std::vector<kitten::K_GameObject*>();
}

std::vector<kitten::K_GameObject*> DecorationGenerator::generateWaterDecoration()
{
	std::vector<kitten::K_GameObject*> list;

	//50% chance it will has one decoration
	float chance = (float)rand() / RAND_MAX;
	if (chance < 0.5)
	{
		kitten::K_GameObject* k = kitten::K_GameObjectManager::getInstance()->createNewGameObject("Decoration_water.json");
		list.push_back(k);
	}

	return list;
}

std::vector<kitten::K_GameObject*> DecorationGenerator::generateSwampDecoration()
{
	std::vector<kitten::K_GameObject*> list;

	//50% chance it will has one decoration
	float chance = (float)rand() / RAND_MAX;
	if (chance < 0.5)
	{
		kitten::K_GameObject* k = kitten::K_GameObjectManager::getInstance()->createNewGameObject("Decoration_swamp.json");
		list.push_back(k);
	}

	return list;
}
