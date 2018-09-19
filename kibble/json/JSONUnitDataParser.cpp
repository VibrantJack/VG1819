#include "jsonextra.hpp"
#include "JSONUnitDataParser.hpp"
#include "Datatypes/UnitDataType.hpp"

UnitData* kibble::JSONUnitDataParser::getUnit(const std::string& p_filename) {
	return getUnitDataFrom(jsonIn(p_filename));
}

std::vector<UnitData*> kibble::JSONUnitDataParser::getUnitList(const std::string& p_filename) {
	return getMultipleUnitDataFrom(jsonIn(p_filename));
}