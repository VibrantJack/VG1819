#pragma once
#include "kibble/GameObjectDataParser.hpp"
#include "kibble/UnitDataParser.hpp"
#include "kibble/DeckDataParser.hpp"
#include <string>


namespace kibble {
	void initializeKibbleRelatedComponents();
	void destroyKibbleRelatedComponents();
	
	GameObjectDataParser* getGameObjectDataParserInstance();
	UnitDataParser* getUnitDataParserInstance();
	DeckDataParser* getDeckDataParserInstance();
	
	void setSceneFrom(const std::string& p_fileName);

	void loadSpriteSheets(const std::string& p_masterSheetName);
	void loadLand(const std::string& p_masterSheetName);
}