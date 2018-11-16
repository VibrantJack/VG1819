#include "TextureBlendMaterial.h"

namespace puppy
{
	TextureBlendMaterial::TextureBlendMaterial() : Material(ShaderType::basic)
	{

	}

	TextureBlendMaterial::~TextureBlendMaterial()
	{
		auto end = m_additionalTextures.cend();
		for (auto it = m_additionalTextures.cbegin(); it != end; ++it)
		{
			delete std::get<0>((*it).second);
		}
	}

	void TextureBlendMaterial::addTexture(const char* p_pathToTexToAdd, const float& p_weight)
	{
		int numTextures = m_additionalTextures.size();
		assert(numTextures + 1 <= MAX_BLEND_TEXTURES);

		std::tuple<Texture*, int, float> toInsert = std::make_tuple(new Texture(p_pathToTexToAdd), numTextures+1, p_weight);

		//Change shader

	}

	void TextureBlendMaterial::removeTexture(const char* p_pathToTexToRemove)
	{
		auto found = m_additionalTextures.find(p_pathToTexToRemove);
		if (found != m_additionalTextures.end())
		{
			delete std::get<0>((*found).second);
			m_additionalTextures.erase(found);
		}
		else
		{
			assert(false);
		}
	}

	void TextureBlendMaterial::apply()
	{
		Material::apply();


	}
}