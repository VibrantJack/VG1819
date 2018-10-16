#include "jsonextra.hpp"
#include "JSONGameObjectDataParser.hpp"
#include "kibble/json/Datatypes/GameObjectDataType.hpp"
#include <string>

constexpr auto GAME_OBJECT_DIRECTORY = "data/gameobject/";

kitten::K_GameObject* kibble::JSONGameObjectDataParser::getGameObject(const std::string& p_filename) {
	return getGameObjectBy(jsonIn(GAME_OBJECT_DIRECTORY + p_filename));
}
