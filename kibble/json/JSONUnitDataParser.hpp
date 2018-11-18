#pragma once
#include "kibble/UnitDataParser.hpp"
#include "unit/UnitCommon.h"

#include <string>

namespace kibble {
	class JSONUnitDataParser : public kibble::UnitDataParser {
	public:
		kibble::UnitFileStruct getUnit(const std::string& p_filename);
	};
}