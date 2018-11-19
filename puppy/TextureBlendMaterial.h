#pragma once

#include "Material.h"
#include <map>


namespace puppy
{
	class TextureBlendMaterial : public Material
	{
	private:
												//Texture,  slot,  weight
		std::map<std::string, std::tuple<Texture*, int, float>> m_additionalTextures;
	public:
		TextureBlendMaterial();
		~TextureBlendMaterial();

		virtual void setTexture(const char* p_pathToTex) override;

		void addTexture(const char* p_pathToTexToAdd, const float& p_weight = 1.0f);
		void removeTexture(const char* p_pathToTexToRemove);

		void changeWeight(const char* p_pathToTex, const float& p_weight);
		int getNumberOfTextures() const;

		Texture* getFirstTexture();

		virtual void apply() override;
	};
}