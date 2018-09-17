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
			//constructors
			Gameboard();
			//consideration: input string or enum type to choose what kind of map is generated
			~Gameboard();
			//methods
			void initialise();
			//members
			kitten::K_GameObject[15][15] m_allTiles;
			static GameBoard* m_Instance;
			int width = 15;
			int depth = 15;
		public:
			//functions
			static GameBoard* getInstance();
			static void CreateInstance();
	};
}