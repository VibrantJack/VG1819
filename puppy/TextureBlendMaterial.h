#pragma once

#include "Material.h"
#include <unordered_map>


namespace puppy
{
	class TextureBlendMaterial : public Material
	{
	private:
												//Texture,  slot,  weight
		std::unordered_map<std::string, std::tuple<Texture*, int, float>> m_additionalTextures;
	public:
		TextureBlendMaterial();
		~TextureBlendMaterial();

		void addTexture(const char* p_pathToTexToAdd, const float& p_weight = 1.0f);
		void removeTexture(const char* p_pathToTexToRemove);

		virtual void apply() override;
	};
}