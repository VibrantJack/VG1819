#pragma once
#include "unit/UnitData.h"

#include <string>
#include <vector>

namespace kibble {
	class UnitDataParser {
	public:
		virtual UnitData* getUnit(const std::string& filename) = 0;
		virtual std::vector<UnitData*> getUnitList(const std::string& filename) = 0;
	};
}