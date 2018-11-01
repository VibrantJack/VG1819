#pragma once
#include "unit/UnitCommon.h"
#include "DeckData.hpp"
#include <vector>

namespace kibble {
	unit::UnitData* getUnitFromId(const int& p_identifier);
	std::vector<unit::UnitData*> getUnitsFromListOfIds(const std::vector<int>& p_identifier);

	//returns null if none is found matching string
	unit::AbilityDescription* getAbilityFromName(const std::string& p_name);

	std::vector<int> getUnitIdsThatHaveAbilityOfName(const std::string& p_name);
	std::vector<int> getUnitIdsThatHaveTag(const std::string& p_tag);

	DeckData* getDeckDataFromId(const int& p_identifier);
	int getDeckDataListCount();
	void addNewDeckData(DeckData*);

	// ===----- For internal Use Only after this comment ---------------------------------------------------

	void setupDatabank();
	void destroyDatabank();
	// returns an empty ability if none is found matching string, adds it internally to a late load list. 
	// To be used only within kibble
	unit::AbilityDescription* getCopyAbilityFromName(const std::string& p_name);
	void flagAbilityForLateLoad(unit::AbilityDescription*);
}