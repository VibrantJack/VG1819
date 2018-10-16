#include "jsonextra.hpp"
#include "JSONUnitDataParser.hpp"
#include "Datatypes/UnitDataType.hpp"

constexpr auto UNIT_DIRECTORY = "data/unit/";

unit::UnitData* kibble::JSONUnitDataParser::getUnit(const std::string& p_filename) {
	return getUnitDataFrom(jsonIn(UNIT_DIRECTORY + p_filename));
}

std::vector<unit::UnitData*> kibble::JSONUnitDataParser::getUnitList(const std::string& p_filename) {
	nlohmann::json jsonfile = jsonIn(UNIT_DIRECTORY + p_filename);
	if (jsonfile.find("units") != jsonfile.end()) {
		return getMultipleUnitDataFrom(jsonfile);
	} 
	else {
		std::vector<unit::UnitData*> dataVector;
		dataVector.push_back(getUnitDataFrom(jsonfile));
		return dataVector;
	}
}