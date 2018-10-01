#pragma once
#include "unit/UnitCommon.h"

#include <string>
#include <vector>

namespace kibble {
	class UnitDataParser {
	public:
		virtual unit::UnitData* getUnit(const std::string& p_filename) = 0;
		virtual std::vector<unit::UnitData*> getUnitList(const std::string& p_filename) = 0;
	};
}