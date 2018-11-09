#include "SpriteLoader.h"
#include "json.hpp"
#include "kibble\json\jsonextra.hpp"

namespace kibble
{
	SpriteLoader* SpriteLoader::sm_instance = nullptr;

	SpriteLoader::SpriteLoader()
	{

	}

	SpriteLoader::~SpriteLoader()
	{
		auto end = m_spriteSheets.cend();
		for (auto it = m_spriteSheets.cbegin(); it != end; ++it)
		{
			delete (*it).second;
		}
	}

	void SpriteLoader::createInstance()
	{
		assert(sm_instance == nullptr);
		sm_instance = new SpriteLoader();
	}

	void SpriteLoader::destroyInstance()
	{
		assert(sm_instance != nullptr);
		delete sm_instance;
		sm_instance = nullptr;
	}

	void SpriteLoader::loadAllSprites(const std::string& p_masterJsonName)
	{
		sm_instance->privateLoadAllSprites(p_masterJsonName);
	}

	void SpriteLoader::privateLoadAllSprites(const std::string& p_masterJsonName)
	{
		nlohmann::json masterFile = jsonIn(SPRITE_SHEET_DIRECTORY + p_masterJsonName);
		auto found = masterFile.find("spritesheets");
		if (found != masterFile.end())
		{
			auto end = masterFile["spritesheets"].cend();
			for (auto it = masterFile["spritesheets"].cbegin(); it != end; ++it)
			{
				loadSpriteSheet(*it);
			}
		}
	}

	void SpriteLoader::loadSpriteSheet(const std::string& p_sheetJsonName)
	{
		//Set sheet info
		nlohmann::json sheetFile = jsonIn(SPRITE_SHEET_DIRECTORY + p_sheetJsonName);

		std::string characterName = sheetFile["name"];
		std::string pathToTex = sheetFile["texture"];

		int sheetWidth = sheetFile["sheetwidth"];
		int sheetHeight = sheetFile["sheetheight"];
		
		int characterWidth = sheetFile["characterwidth"];
		int characterHeight = sheetFile["characterheight"];

		sprites::SpriteSheet* newSheet = new sprites::SpriteSheet(characterName, pathToTex, sheetWidth, sheetHeight, characterWidth, characterHeight);

		//Set animations
		auto end = sheetFile["animations"].cend();
		for (auto it = sheetFile["animations"].cbegin(); it != end; ++it)
		{
			std::string animationName = (*it)["name"];
			
			int startXPosition = (*it)["startpos"][0];
			int startYPosition = (*it)["startpos"][1];
			sprites::SpriteSheet::GridPosition startPos(startXPosition, startYPosition);

			int endXPosition = (*it)["endpos"][0];
			int endYPosition = (*it)["endpos"][1];
			sprites::SpriteSheet::GridPosition endPos(endXPosition, endYPosition);

			float time = (*it)["time"];

			newSheet->setAnimation(animationName, startPos, endPos, time);
		}

		//Set default animation
		std::string defaultAnimation = sheetFile["defaultanimation"];
		newSheet->setDefaultAnimation(defaultAnimation);

		m_spriteSheets.insert(std::make_pair(characterName, newSheet));
	}

	const sprites::SpriteSheet* SpriteLoader::getSpriteSheet(const std::string& p_name) const
	{
		auto found = m_spriteSheets.find(p_name);
		if (found != m_spriteSheets.cend())
		{
			return ((*found).second);
		}
		//else

		return nullptr;
	}
}