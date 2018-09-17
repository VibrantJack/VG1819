#pragma once
#include "kibble/json/jsonextra.hpp"
#include "unit/UnitData.h"
#include <vector>

UnitData* getUnitDataFrom(nlohmann::json jsonfile);

std::vector<UnitData*> getMultipleUnitDataFrom(nlohmann::json jsonfile);