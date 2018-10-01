#pragma once
#include "kibble/GameObjectDataParser.hpp"
#include "kibble/UnitDataParser.hpp"
#include <string>


namespace kibble {
	void initializeKibbleRelatedComponents();
	void destroyKibbleRelatedComponents();
	GameObjectDataParser* getGameObjectDataParserInstance();
	UnitDataParser* getUnitDataParserInstance();
	void setSceneFrom(std::string& filename);
}