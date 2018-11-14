/*@Rock 11.12
Avoid unit spawn, make unit data driven
*/
#pragma once
#include "kibble/json/jsonextra.hpp"
#include "unit/UnitCommon.h"
#include "unit/Unit.h"
#include <vector>

unit::Unit* getUnitFrom(nlohmann::json& p_jsonfile);
unit::Commander* getCommanderFrom(nlohmann::json& p_jsonfile);
unit::AbilityDescription* getADFrom(nlohmann::json& p_jsonfile);
ability::Status* getStatusFrom(nlohmann::json& p_jsonfile);
