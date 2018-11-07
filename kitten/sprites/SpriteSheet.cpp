#include "SpriteSheet.h"

namespace sprites
{
	SpriteSheet::SpriteSheet(const std::string& p_characterName, const std::string& p_pathToSheet, int p_sheetWidth, int p_sheetHeight, int p_characterWidth, int p_characterHeight) : 
		m_characterName(p_characterName),m_sheetWidth(p_sheetWidth), m_sheetHeight(p_sheetHeight), m_characterWidth(p_characterWidth), m_characterHeight(p_characterHeight), 
		m_gridWidth(p_sheetWidth/p_characterWidth), m_gridHeight(p_sheetHeight/p_characterHeight), m_defaultAnimation(nullptr)
	{
		m_material = new puppy::Material(puppy::ShaderType::alphaTest);
		m_material->setTexture(p_pathToSheet.c_str());
	}

	SpriteSheet::~SpriteSheet()
	{
		delete m_material;
	}

	const std::string& SpriteSheet::getCharacterName() const
	{
		return m_characterName;
	}

	void SpriteSheet::setAnimation(const std::string& p_name, const GridPosition& p_startPosition, const GridPosition& p_endPosition)
	{
		AnimationFrame* firstFrame = new AnimationFrame();

		//Chain together frames from startPosition to endPosition

		m_animations.insert(std::make_pair(p_name, firstFrame));
	}

	void SpriteSheet::setDefaultAnimation(const std::string& p_name)
	{
		auto found = m_animations.find(p_name);
		if (found != m_animations.cend())
		{
			m_defaultAnimation = &((*found).second);
		}
	}

	const SpriteSheet::AnimationFrame* SpriteSheet::getAnimation(const std::string& p_name) const
	{
		auto found = m_animations.find(p_name);
		if (found != m_animations.cend())
		{
			return &(*found).second;
		}
		return nullptr;
	}

	const SpriteSheet::AnimationFrame* SpriteSheet::getDefaultAnimation() const
	{
		return m_defaultAnimation;
	}
}