#pragma once
#include "kibble.hpp"
#include "json/JSONComponentDataParser.hpp"
#include "kibble/json/Datatypes/ComponentDataType.hpp"
#include "kibble/json/JSONGameObjectDataParser.hpp"
#include "kibble/json/JSONUnitDataParser.hpp"

kibble::GameObjectDataParser* gameObjectParser;
kibble::UnitDataParser* unitParser;

void kibble::initializeKibbleRelatedComponents() {
	setupComponentMap();

	gameObjectParser = new JSONGameObjectDataParser();
	unitParser = new JSONUnitDataParser();
}

void kibble::destroyKibbleRelatedComponents() {
	delete gameObjectParser;
	delete unitParser;
}

kibble::GameObjectDataParser* kibble::getGameObjectDataParserInstance() {
	return gameObjectParser;
}

kibble::UnitDataParser* kibble::getUnitDataParserInstance() {
	return unitParser;
}

#include "kibble/json/Datatypes/SceneDataType.hpp"
void kibble::setSceneFrom(std::string& filename) {
	setupSceneBy(jsonIn("data/scene/" + filename));
}