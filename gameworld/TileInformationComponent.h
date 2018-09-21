//Austin Rogers - 9/13/18
//Generic Tile Imformation component the defines a game object as a "tile" on the game board.
#pragma once

#include "kitten\K_Component.h"
#include <iostream>

namespace gameworld
{
	class TileInformationComponent : public kitten::K_Component
	{
	public:
		TileInformationComponent() 
		{
			//blank for later
		}

		~TileInformationComponent()
		{
			//blank for later
		};

		//========================================================
		//New types will be added here later
		enum TileType {
			type_Unknown,
			type_Grassland,
		};
		//========================================================

		TileType GetType()
		{
			return m_Type;
		};

		const std::string getTexturePath()
		{
			return m_TexturePath;
		}

	protected:
		TileType m_Type = type_Unknown;
		std::string m_TexturePath = "textures/MISSING.tga";
	};
}