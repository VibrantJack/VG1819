#pragma once
#include "unit/UnitCommon.h"

#include <vector>

namespace kibble {
	void setupDatabank();
	void destroyDatabank();
	unit::UnitData* getUnitFromId(const int& Identifier);
	std::vector<unit::UnitData*> getUnitsFromListOfIds(const std::vector<int>& Identifier);

	//returns null if none is found matching string
	unit::AbilityDescription* getAbilityFromName(const std::string& p_name);

	std::vector<int> getUnitIdsThatHaveAbilityOfName(const std::string& p_name);
	std::vector<int> getUnitIdsThatHaveTag(const std::string& p_tag);

	// ===-----For internal Use Only after this comment ---------------------------------------------------

	// returns an empty ability if none is found matching string, adds it internally to a late load list. 
	// To be used only within kibble
	unit::AbilityDescription* getAnyAbilityFromName(const std::string& p_name);
	void addAbilityToLateLoadUpdate(unit::AbilityDescription*);
}