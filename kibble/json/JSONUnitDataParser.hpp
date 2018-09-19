#pragma once
#include "kibble/UnitDataParser.hpp"
#include "unit/UnitData.h"

#include <string>

namespace kibble {
	class JSONUnitDataParser : public kibble::UnitDataParser {
	public:
		UnitData* getUnit(const std::string& filename);
		std::vector<UnitData*> getUnitList(const std::string& filename);
	};
}