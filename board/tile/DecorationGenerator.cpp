#include "DecorationGenerator.h"
#include "kitten/K_GameObjectManager.h"

std::vector<kitten::K_GameObject*> DecorationGenerator::generateDecoration(LandInformation::TileType p_type)
{
	switch (p_type)
	{
	case LandInformation::Grass_land:
		return generateGrassDecoration();

	}
	return std::vector<kitten::K_GameObject*>();
}


std::vector<kitten::K_GameObject*> DecorationGenerator::generateGrassDecoration()
{
	std::vector<kitten::K_GameObject*> list;

	//int n = rand() % MAX_DECO_NUM;//number of decoration

	int n = 1;

	for (int i = 0; i < n; i++)
	{
		kitten::K_GameObject* k = kitten::K_GameObjectManager::getInstance()->createNewGameObject("Decoration_grass.json");
		list.push_back(k);
	}

	return list;
}
