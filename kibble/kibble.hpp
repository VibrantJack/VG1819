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
	void setSceneFrom(std::string& filename);
}