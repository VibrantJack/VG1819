#include "SquareBorder.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"


SquareBorder::SquareBorder()
{
}


SquareBorder::~SquareBorder()
{
	//todo
}

void SquareBorder::start()
{
	kitten::K_GameObjectManager* GOM = kitten::K_GameObjectManager::getInstance();
	
	kitten::K_GameObject* topBorder = GOM->createNewGameObject("UIElement");

	//you need to make a kibble object that makes the frame pieces with the texture atlas. 
	//the frame piece class should have a enum type that tells it what UVs to use for different parts of the frame.

	//you should be able to createGameObject("TopFrame"); and get the top piece
	//pieces should be components that listen to the master object's position and adjust themselves as needed.
}


