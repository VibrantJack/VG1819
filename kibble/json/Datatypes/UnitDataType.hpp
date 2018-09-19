#pragma once
#include "kibble/json/jsonextra.hpp"
#include "unit/UnitData.h"
#include <vector>

unit::UnitData* getUnitDataFrom(nlohmann::json& p_jsonfile);

std::vector<unit::UnitData*> getMultipleUnitDataFrom(nlohmann::json& p_jsonfile);