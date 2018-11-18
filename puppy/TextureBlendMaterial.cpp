#include "TextureBlendMaterial.h"

namespace puppy
{
	TextureBlendMaterial::TextureBlendMaterial() : Material(ShaderType::texture_blend_zero)
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

	void TextureBlendMaterial::setTexture(const char* p_pathToTex)
	{
		addTexture(p_pathToTex);
	}

	void TextureBlendMaterial::addTexture(const char* p_pathToTexToAdd, const float& p_weight)
	{
		int numTextures = m_additionalTextures.size();
		assert(numTextures + 1 <= MAX_BLEND_TEXTURES);

		std::tuple<Texture*, int, float> toInsert = std::make_tuple(new Texture(p_pathToTexToAdd, numTextures), numTextures+1, p_weight);

		//Change shader
		m_shader = ShaderManager::getShaderProgram(static_cast<ShaderType>(ShaderType::texture_blend_zero + numTextures));
	}

	void TextureBlendMaterial::removeTexture(const char* p_pathToTexToRemove)
	{
		auto found = m_additionalTextures.find(p_pathToTexToRemove);
		if (found != m_additionalTextures.end())
		{
			delete std::get<0>((*found).second);
			m_additionalTextures.erase(found);

			m_shader = ShaderManager::getShaderProgram(static_cast<ShaderType>(ShaderType::texture_blend_zero + m_additionalTextures.size()));
		}
		else
		{
			assert(false);
		}
	}
	
	void TextureBlendMaterial::changeWeight(const char* p_pathToTex, const float& p_weight)
	{
		auto found = m_additionalTextures.find(p_pathToTex);

		assert(found != m_additionalTextures.cend());

		float& oldWeight = std::get<2>((*found).second);
		oldWeight = p_weight;
	}

	void TextureBlendMaterial::apply()
	{
		ShaderManager::applyShader(m_shader);

		//Apply textures
		auto end = m_additionalTextures.cend();
		for (auto it = m_additionalTextures.cbegin(); it != end; ++it)
		{
			auto texTuple = (*it).second;
			std::get<0>(texTuple)->apply();

			//Set weight
			setUniform(TEXTURE_BLEND_WEIGHT_UNIFORM_NAME+std::get<1>(texTuple),std::get<2>(texTuple));
		}
	}
}