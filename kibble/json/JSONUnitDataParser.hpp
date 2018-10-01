#pragma once
#include "kibble/UnitDataParser.hpp"
#include "unit/UnitCommon.h"

#include <string>

namespace kibble {
	class JSONUnitDataParser : public kibble::UnitDataParser {
	public:
		unit::UnitData* getUnit(const std::string& filename);
		std::vector<unit::UnitData*> getUnitList(const std::string& p_filename);
	};
}