#include "TextureBlendMaterial.h"

namespace puppy
{
	TextureBlendMaterial::TextureBlendMaterial(bool p_isLit) : Material(p_isLit ? ShaderType::texture_blend_zero_point_light : ShaderType::texture_blend_zero),
		m_baseShader(p_isLit ? ShaderType::texture_blend_zero_point_light : ShaderType::texture_blend_zero), m_ownedTexture(nullptr)
	{
		
	}

	TextureBlendMaterial::~TextureBlendMaterial()
	{
		//We don't own the textures in m_textures except m_ownedTexture

		if (m_ownedTexture != nullptr)
		{
			delete m_ownedTexture;
		}
	}

	Material* TextureBlendMaterial::clone() const
	{
		TextureBlendMaterial* toReturn = new TextureBlendMaterial();

		auto end = m_textures.cend();
		for (auto it = m_textures.cbegin(); it != end; ++it)
		{
			Texture* clonedTex = new Texture((*it).first->getPath());
			toReturn->m_textures.insert(std::make_pair(clonedTex, (*it).second));
		}

		if (m_ownedTexture != nullptr)
		{
			toReturn->m_ownedTexture = new Texture(m_ownedTexture->getPath());
		}

		toReturn->m_shader = m_shader;
		toReturn->m_baseShader = m_baseShader;

		toReturn->m_hasColour = m_hasColour;
		toReturn->m_colour = m_colour;
		
		toReturn->m_hasMatLightProperties = m_hasMatLightProperties;
		toReturn->m_matAmbient = m_matAmbient;
		toReturn->m_matDiffuse = m_matDiffuse;

		return toReturn;
	}

	bool TextureBlendMaterial::operator==(const Material& p_other) const
	{
		if (typeid(*this) != typeid(p_other))
		{
			return false;
		}

		if (m_hasColour != p_other.hasColour())
		{
			return false;
		}

		if (m_hasColour)
		{
			if (m_colour != p_other.getColour())
			{
				return false;
			}
		}

		if (m_hasMatLightProperties != p_other.hasMatLightProperties())
		{
			return false;
		}

		if (m_hasMatLightProperties)
		{
			if (m_matAmbient != p_other.getMatAmbient())
			{
				return false;
			}

			if (m_matDiffuse != p_other.getMatDiffuse())
			{
				return false;
			}
		}

		//else, equal if textures and weights are the same
		const TextureBlendMaterial& castedOther = static_cast<const TextureBlendMaterial&>(p_other);

		if (m_ownedTexture != nullptr && castedOther.m_ownedTexture != nullptr)
		{
			if (m_ownedTexture->getTex() != castedOther.m_ownedTexture->getTex())
			{
				return false;
			}
		}

		if (m_textures.size() == castedOther.m_textures.size())
		{
			auto otherTexturesMap = castedOther.m_textures;
			auto end = m_textures.cend();
			for (auto it = m_textures.cbegin(); it != end; ++it)
			{
				auto tex = (*it).first;
				
				//Search through the other map for the matching texture; can't compare pointers
				bool foundMatch = false;
				float foundWeight = 0.0f;
				for (auto otherIt = otherTexturesMap.cbegin(); otherIt != otherTexturesMap.end(); ++otherIt)
				{
					auto otherTex = (*otherIt).first;
					if (otherTex->getTex() == tex->getTex())
					{
						foundMatch = true;
						foundWeight = (*otherIt).second;
						otherTexturesMap.erase(otherIt); // This is erasing from a copy of the other map.
						break;
					}
				}

				if (!foundMatch)
				{
					return false;
				}
				//else compare weights

				if (foundWeight != (*it).second)
				{
					return false;
				}
			}

			return true;
		}
		else
		{
			//The number of textures are different, can't have same textures
			return false;
		}
	}

	void TextureBlendMaterial::setTexture(const char* p_pathToTex)
	{
		if (m_ownedTexture != nullptr)
		{
			m_textures.erase(m_ownedTexture);
			delete m_ownedTexture;
		}

		m_ownedTexture = new Texture(p_pathToTex);
		addTexture(m_ownedTexture);
	}

	Texture* TextureBlendMaterial::getOwnedTexture()
	{
		return m_ownedTexture;
	}

	void TextureBlendMaterial::addTexture(Texture* p_tex, const float& p_weight)
	{
		m_textures.insert(std::make_pair(p_tex, p_weight));
		m_shader = ShaderManager::getShaderProgram(static_cast<ShaderType>(m_baseShader + m_textures.size() - 1));
	}

	void TextureBlendMaterial::removeTexture(Texture* p_tex)
	{
		m_textures.erase(p_tex);
		m_shader = ShaderManager::getShaderProgram(static_cast<ShaderType>(m_baseShader + m_textures.size() -1));
	}

	void TextureBlendMaterial::changeWeight(Texture* p_tex, const float& p_weight)
	{
		auto found = m_textures.find(p_tex);
		if (found != m_textures.cend())
		{
			auto& pair = *found;	
			pair.second = p_weight;
		}
	}

	int TextureBlendMaterial::getNumberOfTextures() const
	{
		return m_textures.size();
	}

	void TextureBlendMaterial::apply() const
	{
		bool wasBound = ShaderManager::applyShader(m_shader);

		if (wasBound)
		{
			//Set texture (sampler) uniforms
			if (m_shader->getType() > texture_blend_zero)
			{
				int texUniforms = m_shader->getType() - m_baseShader;
				for (int i = 1; i <= texUniforms; ++i)
				{
					setUniform(SAMPLER2D_NAME + std::to_string(i), i);
				}
			}
		}

		int i = 0;
		auto end = m_textures.cend();
		for (auto it = m_textures.cbegin(); it != end; ++it)
		{
			auto pair = (*it);
			auto tex = pair.first;
			tex->setSlot(i);
			tex->apply();

			std::string uniformName = TEXTURE_BLEND_WEIGHT_UNIFORM_NAME;
			uniformName += std::to_string(i);
			setUniform(uniformName, pair.second);


			++i;
		}

		applyMatLightProperties();
	}
}