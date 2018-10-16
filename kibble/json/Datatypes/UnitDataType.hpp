#pragma once
#include "kibble/json/jsonextra.hpp"
#include "unit/UnitCommon.h"
#include <vector>

unit::UnitData* getUnitDataFrom(nlohmann::json& p_jsonfile);

std::vector<unit::UnitData*> getMultipleUnitDataFrom(nlohmann::json& p_jsonfile);

unit::AbilityDescription* getAbilityDescriptionFrom(nlohmann::json& p_jsonfile);
unit::StatusDescription* getStatusDescriptionFrom(nlohmann::json& p_jsonfile);