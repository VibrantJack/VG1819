#include "jsonextra.hpp"
#include "JSONUnitDataParser.hpp"
#include "Datatypes/UnitDataType.hpp"

UnitData* kibble::JSONUnitDataParser::getUnit(const std::string& filename) {
	return getUnitDataFrom(jsonIn(filename));
}

std::vector<UnitData*> kibble::JSONUnitDataParser::getUnitList(const std::string& filename) {
	return getMultipleUnitDataFrom(jsonIn(filename));
}