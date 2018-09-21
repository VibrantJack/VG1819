#pragma once
#include "kibble/UnitDataParser.hpp"
#include "unit/UnitData.h"

#include <string>

namespace kibble {
	class JSONUnitDataParser : public kibble::UnitDataParser {
	public:
		unit::UnitData* getUnit(const std::string& filename);
		std::vector<unit::UnitData*> getUnitList(const std::string& p_filename);
	};
}