#include "jsonextra.hpp"
#include "JSONUnitDataParser.hpp"
#include "Datatypes/UnitDataType.hpp"

UnitData* kibble::JSONUnitDataParser::getUnit(std::string filename) {
	return getUnitDataFrom(jsonIn(filename));
}

std::vector<UnitData*> kibble::JSONUnitDataParser::getUnitList(std::string filename) {
	return getMultipleUnitDataFrom(jsonIn(filename));
}