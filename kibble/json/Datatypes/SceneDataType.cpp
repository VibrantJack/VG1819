#include "GameObjectDataType.hpp"
#include "kitten/K_GameObjectManager.h"

void setupSceneBy(nlohmann::json& p_jsonfile) {

	if (p_jsonfile.find("scenes") != p_jsonfile.end()) {
		for (nlohmann::json::iterator it = p_jsonfile["scenes"].begin(); it != p_jsonfile["scenes"].end(); ++it) {
			std::string filename = it.value();
			setupSceneBy(jsonIn("data/scene/" + filename));
		}
	}
	// loop through game objects
	if (p_jsonfile.find("gameobjects") != p_jsonfile.end()) {
		//assert(p_jsonfile["gameobjects"].is_array());
		for (nlohmann::json::iterator it = p_jsonfile["gameobjects"].begin(); it != p_jsonfile["gameobjects"].end(); ++it) {
			kitten::K_GameObject* gameobject = getGameObjectBy(*it);
		}
	}
}