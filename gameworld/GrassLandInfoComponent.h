#pragma once
//@ Austin Rogers 09/15/18

#include "TileInformationComponent.h"

namespace gameworld
{
	class GrasslandInfoComponent : public gameworld::TileInformationComponent
	{
	public:
		GrasslandInfoComponent(nlohmann::json& p_json) : gameworld::TileInformationComponent(p_json) {
			m_Type = TileInformationComponent::type_Grassland;
			m_TexturePath = "tiles/Grassland.tga";
		}

		GrasslandInfoComponent() {
			m_Type = TileInformationComponent::type_Grassland;
			m_TexturePath = "tiles/Grassland.tga";
		}
	};
}