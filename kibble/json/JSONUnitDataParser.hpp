/*
Interface between the under belly of the parser and the actual game. 
*/
#include "kibble/UnitDataParser.hpp"
#include "unit/UnitData.h"

#include <string>

namespace kibble {
	class JSONUnitDataParser : public kibble::UnitDataParser {
	public:
		UnitData* getUnit(std::string filename);
		std::vector<UnitData*> getUnitList(std::string filename);
	};
}