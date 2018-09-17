#include "json.hpp"
#include "JSONDataParserFactory.hpp"

#include <fstream>

nlohmann::json jsonIn(std::string filename) {
	std::ifstream input(filename);
	nlohmann::json jsontarget;
	input >> jsontarget;
	return jsontarget;
}

kitten::K_GameObject* kibble::JSONDataParserFactory::getGameObject(std::string filename) {
	
	return nullptr;
}

#include "Datatypes/UnitDataType.hpp"
UnitData* kibble::JSONDataParserFactory::getUnit(std::string filename) {
	return getUnitDataFrom(jsonIn(filename));
}