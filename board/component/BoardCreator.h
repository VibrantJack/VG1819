#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_GameObject.h"

class BoardCreator
{
public:
	BoardCreator();
	~BoardCreator();

	kitten::K_GameObject* createTile(int x, int z);
	kitten::K_GameObject* getTile(int x, int z);
};