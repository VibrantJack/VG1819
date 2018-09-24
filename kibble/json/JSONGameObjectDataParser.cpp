#include "jsonextra.hpp"
#include "JSONGameObjectDataParser.hpp"
#include "kibble/json/Datatypes/GameObjectDataType.hpp"
#include <string>

kitten::K_GameObject* kibble::JSONGameObjectDataParser::getGameObject(const std::string& p_filename) {
	return getGameObjectBy(jsonIn(p_filename));
}
