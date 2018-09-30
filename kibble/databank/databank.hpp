#pragma once
#include "unit/UnitCommon.h"

#include <vector>

namespace kibble {
	void setupDatabank();
	void destroyDatabank();
	unit::UnitData* getUnitFromId(const int& Identifier);
	std::vector<unit::UnitData*> getUnitsFromListOfIds(const std::vector<int>& Identifier);
}