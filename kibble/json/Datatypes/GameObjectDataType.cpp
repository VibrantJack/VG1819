#include "GameObjectDataType.hpp"
#include "kitten/K_GameObjectManager.h"
#include "kitten/K_ComponentManager.h"
#include "kibble/json/Datatypes/ComponentDataType.hpp"

kitten::K_GameObject* getGameObjectBy(nlohmann::json& p_jsonFile, kitten::K_GameObject* p_baseObj) {

	// going through both managers is important! 
	kitten::K_GameObjectManager* gameObjectManager = kitten::K_GameObjectManager::getInstance();
	kitten::K_ComponentManager* componentManager = kitten::K_ComponentManager::getInstance();
	kitten::K_GameObject* gameObject;

	// start off with checking for filename to base things on
	if (p_baseObj == nullptr) {
		if (p_jsonFile.find("filename") != p_jsonFile.end()) {
			gameObject = gameObjectManager->createNewGameObject(p_jsonFile["filename"]);
		}
		else {
			gameObject = gameObjectManager->createNewGameObject();
		}
	}
	else {
		gameObject = p_baseObj;
	}
	

	// add all attributes related to game object only here!
	if (p_jsonFile.find("translate") != p_jsonFile.end()) {
		gameObject->getTransform().place(p_jsonFile["translate"][0], p_jsonFile["translate"][1], p_jsonFile["translate"][2]);
	}

	if (p_jsonFile.find("rotate") != p_jsonFile.end()) {
		gameObject->getTransform().rotateAbsolute(glm::vec3(p_jsonFile["rotate"][0], p_jsonFile["rotate"][1], p_jsonFile["rotate"][2]));
	}

	if (p_jsonFile.find("scale") != p_jsonFile.end()) {
		gameObject->getTransform().scaleAbsolute(p_jsonFile["scale"][0], p_jsonFile["scale"][1], p_jsonFile["scale"][2]);
	}

	if (p_jsonFile.find("translate2d") != p_jsonFile.end()) {
		gameObject->getTransform().place2D(p_jsonFile["translate2d"][0], p_jsonFile["translate2d"][1]);
	}

	if (p_jsonFile.find("rotate2d") != p_jsonFile.end()) {
		gameObject->getTransform().rotate2D(p_jsonFile["rotate2d"]);
	}

	auto scaleInWorldFound = p_jsonFile.find("worldscale");
	if (scaleInWorldFound != p_jsonFile.end()) {
		gameObject->getTransform().scaleInWorld((*scaleInWorldFound)[0], (*scaleInWorldFound)[1], (*scaleInWorldFound)[2]);
	}

	if (p_jsonFile.find("scale2d") != p_jsonFile.end()) {
		gameObject->getTransform().scale2D(p_jsonFile["scale2d"][0], p_jsonFile["scale2d"][1]);
	}

	if (p_jsonFile.find("components") != p_jsonFile.end()) {
		//assert(p_jsonfile["components"].is_array());
		for (nlohmann::json::iterator it = p_jsonFile["components"].begin(); it != p_jsonFile["components"].end(); ++it) {
			gameObject->addComponent(componentManager->createComponent(&*it));
		}
	}

	if (p_jsonFile.find("gameobjects") != p_jsonFile.end()) {
		//assert(p_jsonfile["components"].is_array());
		for (nlohmann::json::iterator it = p_jsonFile["gameobjects"].begin(); it != p_jsonFile["gameobjects"].end(); ++it) {
			
			kitten::K_GameObject* child = gameObjectManager->createNewGameObject();
			
			child->getTransform().setParent(&gameObject->getTransform());
			child->getTransform().setIgnoreParent(false);

			child = getGameObjectBy(*it, child);
			
			
		}
	}

	return gameObject;
}