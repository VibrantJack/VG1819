#include "SpriteSheet.h"

namespace sprites
{
	SpriteSheet::SpriteSheet(const std::string& p_characterName, int p_sheetWidth, int p_sheetHeight, int p_characterWidth, int p_characterHeight) : 
		m_characterName(p_characterName),m_sheetWidth(p_sheetWidth), m_sheetHeight(p_sheetHeight), m_characterWidth(p_characterWidth), m_characterHeight(p_characterHeight), 
		m_gridWidth(p_sheetWidth/p_characterWidth), m_gridHeight(p_sheetHeight/p_characterHeight)
	{

	}

	SpriteSheet::~SpriteSheet()
	{

	}

	const std::string& SpriteSheet::getCharacterName()
	{
		return m_characterName;
	}

	void SpriteSheet::setAnimation(const std::string& p_name, const AnimationData& p_data)
	{
		m_animations.insert(std::make_pair(p_name, p_data));
	}

	const SpriteSheet::AnimationData& SpriteSheet::getAnimation(const std::string& p_name)
	{
		return m_animations[p_name];
	}

	
}