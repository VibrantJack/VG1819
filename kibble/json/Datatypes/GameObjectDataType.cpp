#include "GameObjectDataType.hpp"
#include "kitten/K_GameObjectManager.h"
#include "kitten/K_ComponentManager.h"
#include "kibble/json/Datatypes/ComponentDataType.hpp"

kitten::K_GameObject* getGameObjectBy(nlohmann::json& p_jsonfile) {

	// going through both managers is important! 
	kitten::K_GameObjectManager* gameobjectmanager = kitten::K_GameObjectManager::getInstance();
	kitten::K_ComponentManager* componentmanager = kitten::K_ComponentManager::getInstance();
	kitten::K_GameObject* gameobject;

	// start off with checking for filename to base things on
	if (p_jsonfile.find("filename") != p_jsonfile.end()) {
		gameobject = gameobjectmanager->createNewGameObject(p_jsonfile["filename"]);
	}
	else {
		gameobject = gameobjectmanager->createNewGameObject();
	}

	// add all attributes related to game object only here!
	if (p_jsonfile.find("translate") != p_jsonfile.end()) {
		gameobject->getTransform().place(p_jsonfile["translate"][0], p_jsonfile["translate"][1], p_jsonfile["translate"][2]);
	}

	if (p_jsonfile.find("rotate") != p_jsonfile.end()) {
		gameobject->getTransform().rotateAbsolute(glm::vec3(p_jsonfile["rotate"][0], p_jsonfile["rotate"][1], p_jsonfile["rotate"][2]));
	}

	if (p_jsonfile.find("scale") != p_jsonfile.end()) {
		gameobject->getTransform().scaleAbsolute(p_jsonfile["scale"][0], p_jsonfile["scale"][1], p_jsonfile["scale"][2]);
	}

	if (p_jsonfile.find("translate2d") != p_jsonfile.end()) {
		gameobject->getTransform().place2D(p_jsonfile["translate2d"][0], p_jsonfile["translate2d"][1]);
	}

	if (p_jsonfile.find("rotate2d") != p_jsonfile.end()) {
		gameobject->getTransform().rotate2D(p_jsonfile["rotate2d"]);
	}

	if (p_jsonfile.find("scale2d") != p_jsonfile.end()) {
		gameobject->getTransform().scale2D(p_jsonfile["scale2d"][0], p_jsonfile["scale2d"][1]);
	}

	if (p_jsonfile.find("components") != p_jsonfile.end()) {
		//assert(p_jsonfile["components"].is_array());
		for (nlohmann::json::iterator it = p_jsonfile["components"].begin(); it != p_jsonfile["components"].end(); ++it) {
			gameobject->addComponent(componentmanager->createComponent(&*it));
		}
	}

	return gameobject;
}