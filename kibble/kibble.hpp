#pragma once
#include "kibble/GameObjectDataParser.hpp"
#include "kibble/UnitDataParser.hpp"

namespace kibble {
	void initializeKibbleRelatedComponents();
	void destroyKibbleRelatedComponents();
	GameObjectDataParser* getGameObjectDataParserInstance();
	UnitDataParser* getUnitDataParserInstance();
}