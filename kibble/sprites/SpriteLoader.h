#pragma once
#include <unordered_map>
#include <string>
#include "kitten\sprites\SpriteSheet.h"

#define SPRITE_SHEET_DIRECTORY "data/sprites/"

namespace sprites
{
	class SpriteAnimator;
}

namespace kibble
{
	class SpriteLoader
	{
		friend class sprites::SpriteAnimator;
	private:
		SpriteLoader();
		~SpriteLoader();
		static SpriteLoader* sm_instance;

		std::unordered_map<std::string, sprites::SpriteSheet*> m_spriteSheets;

		const sprites::SpriteSheet* getSpriteSheet(const std::string& p_spriteName) const;

		void loadSpriteSheet(const std::string& p_sheetJsonName);
	public:
		void createInstance();
		void destroyInstance();

		void loadAllSprites(const std::string& p_masterJsonName);
	};
}