#pragma once
//@Austin Rogers 9/16/18
//used to assemble a data structure of tile components that are rendered on the screen as a gameboard

#include "gameworld/TileInformationComponent.h"
#include "gameworld/GrasslandInfoComponent.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_Component.h"
#include "kitten\K_GameObject.h"
#include <array>

namespace gameworld
{
	class GameBoard : public kitten::K_Component
	{
		private:
			//methods
			void initialise();
			//members
			kitten::K_GameObject m_allTiles[15][15];
			static GameBoard* m_Instance;
			int width = 15;
			int depth = 15;
		public:
			//constructors
			GameBoard();
			//consideration: input string or enum type to choose what kind of map is generated
			~GameBoard();
			//functions
			static GameBoard* getInstance();
			static void CreateInstance();
	};
}