#pragma once
#include "kibble.hpp"
#include "databank/databank.hpp"
#include "kibble/json/Datatypes/ComponentDataType.hpp"
#include "kibble/json/JSONGameObjectDataParser.hpp"
#include "kibble/json/JSONUnitDataParser.hpp"
#include "kibble/custom/CustomDeckDataParser.hpp"

kibble::GameObjectDataParser* gameObjectParser;
kibble::UnitDataParser* unitParser;
kibble::DeckDataParser* deckParser;

void kibble::initializeKibbleRelatedComponents() {
	setupComponentMap();

	gameObjectParser = new JSONGameObjectDataParser();
	unitParser = new JSONUnitDataParser();
	deckParser = new CustomDeckDataParser();

	setupDatabank();
}

void kibble::destroyKibbleRelatedComponents() {
	destroyDatabank();

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
void kibble::setSceneFrom(std::string& filename) {
	setupSceneBy(jsonIn("data/scene/" + filename));
}
