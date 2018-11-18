#pragma once
#include "unit/UnitCommon.h"
#include "json/jsonextra.hpp"

#include <string>
#include <vector>

namespace kibble {
	struct UnitFileStruct {
		unit::UnitData* data;
		std::vector<nlohmann::json> components;
		float rotate[3] = { 0 }, scale[3] = { 1, 1, 1 }, translate[3] = { 0 };
	};

	class UnitDataParser {
	public:
		virtual UnitFileStruct getUnit(const std::string& p_filename) = 0;
	};
}