#pragma once
#include "kibble/json/jsonextra.hpp"
#include "unit/UnitData.h"
#include <vector>

UnitData* getUnitDataFrom(nlohmann::json& p_jsonfile);

std::vector<UnitData*> getMultipleUnitDataFrom(nlohmann::json& p_jsonfile);