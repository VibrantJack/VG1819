#pragma once
//@ Austin Rogers 09/15/18

#include "TileInformationComponent.h"

namespace gameworld
{
	class GrasslandInfoComponent : public gameworld::TileInformationComponent
	{
	public:
		GrasslandInfoComponent() {
			m_Type = TileInformationComponent::type_Grassland;
			m_TexturePath = "tiles/Grassland.tga";
		}
	};
}