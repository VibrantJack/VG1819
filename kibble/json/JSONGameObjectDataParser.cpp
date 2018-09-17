#include "jsonextra.hpp"
#include "JSONGameObjectDataParser.hpp"
#include "JSONComponentDataParser.hpp"
#include "kitten/K_GameObjectManager.h"
#include "kitten/K_ComponentManager.h"
#include <string>
kitten::K_GameObject* kibble::JSONGameObjectDataParser::getGameObject(std::string filename) {
	kitten::K_GameObjectManager* gameobjectmanager = kitten::K_GameObjectManager::getInstance();
	kitten::K_ComponentManager* componentmanager = kitten::K_ComponentManager::getInstance();
	kitten::K_GameObject* gameobject = gameobjectmanager->createNewGameObject();
	nlohmann::json jsonfile = jsonIn(filename);

	// add all attributes related to game object only here!

	if (jsonfile.find("components") != jsonfile.end()) {
		assert(jsonfile["components"].is_array());
		for (nlohmann::json::iterator it = jsonfile["components"].begin(); it != jsonfile["components"].end(); ++it) {
			JSONComponentDataParser data = JSONComponentDataParser(&(*it));
			gameobject->addComponent(componentmanager->createComponent(&data));
		}
	}

	return gameobject;
}
