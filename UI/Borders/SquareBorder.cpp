#include "SquareBorder.h"
#include "kitten\K_ComponentManager.h"
#include "kibble\kibble.hpp"

namespace userinterface
{
	SquareBorder::SquareBorder()
	{
	}


	SquareBorder::~SquareBorder()
	{
		//todo
	}

	void SquareBorder::start()
		
	{
		kitten::K_ComponentManager* compMan = kitten::K_ComponentManager::createComponent()
		kitten::K_GameObject* topPiece = kibble::getGameObjectDataParserInstance()->getGameObject("ui/borders/border_piece.txt");
		

		//you need to make a kibble object that makes the frame pieces with the texture atlas. 
		//the frame piece class should have a enum type that tells it what UVs to use for different parts of the frame.

		//you should be able to createGameObject("TopFrame"); and get the top piece
		//pieces should be components that listen to the master object's position and adjust themselves as needed.
	}
}


