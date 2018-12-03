#pragma once
#include "kibble.hpp"
#include "databank/databank.hpp"
#include "kibble/json/Datatypes/ComponentDataType.hpp"
#include "kibble/json/JSONGameObjectDataParser.hpp"
#include "kibble/json/JSONUnitDataParser.hpp"
#include "kibble/custom/CustomDeckDataParser.hpp"
#include "kibble\sprites\SpriteLoader.h"

kibble::GameObjectDataParser* gameObjectParser;
kibble::UnitDataParser* unitParser;
kibble::DeckDataParser* deckParser;
kibble::SpriteLoader* spriteLoader;

void kibble::initializeKibbleRelatedComponents() {
	setupComponentMap();

	gameObjectParser = new JSONGameObjectDataParser();
	unitParser = new JSONUnitDataParser();
	deckParser = new CustomDeckDataParser();
	SpriteLoader::createInstance();

	setupDatabank();
}

void kibble::destroyKibbleRelatedComponents() {
	destroyDatabank();
	SpriteLoader::destroyInstance();

	delete gameObjectParser;
	delete unitParser;
	delete deckParser;
}

kibble::GameObjectDataParser* kibble::getGameObjectDataParserInstance() {
	return gameObjectParser;
}

kibble::UnitDataParser* kibble::getUnitDataParserInstance() {
	return unitParser;
}

kibble::DeckDataParser* kibble::getDeckDataParserInstance() {
	return deckParser;
}

#include "kibble/json/Datatypes/SceneDataType.hpp"
void kibble::setSceneFrom(const std::string& fileName) {
	setupSceneBy(jsonIn("data/scene/" + fileName));
}

void kibble::loadSpriteSheets(const std::string& p_masterSheetName){
	SpriteLoader::loadAllSprites(p_masterSheetName);
}