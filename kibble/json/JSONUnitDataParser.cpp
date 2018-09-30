#include "jsonextra.hpp"
#include "JSONUnitDataParser.hpp"
#include "Datatypes/UnitDataType.hpp"

const std::string UNITFILEDIRECTORY = "data/unit/";

unit::UnitData* kibble::JSONUnitDataParser::getUnit(const std::string& p_filename) {
	return getUnitDataFrom(jsonIn(UNITFILEDIRECTORY + p_filename));
}

std::vector<unit::UnitData*> kibble::JSONUnitDataParser::getUnitList(const std::string& p_filename) {
	nlohmann::json jsonfile = jsonIn(UNITFILEDIRECTORY + p_filename);
	if (jsonfile.find("units") != jsonfile.end()) {
		return getMultipleUnitDataFrom(jsonfile);
	} 
	else {
		std::vector<unit::UnitData*> dataVector;
		dataVector.push_back(getUnitDataFrom(jsonfile));
		return dataVector;
	}
}