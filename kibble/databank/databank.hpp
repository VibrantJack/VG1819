#pragma once
#include "unit/UnitCommon.h"
#include "DeckData.hpp"
#include <vector>
#include "kitten/K_GameObject.h"

namespace kibble {
	unit::Unit* getUnitFromId(const int& p_identifier);
	std::vector<unit::Unit*> getUnitsFromListOfIds(const std::vector<int>& p_identifier);

	//returns null if none is found matching string
	unit::AbilityDescription* getAbilityFromName(const std::string& p_name);

	std::vector<int> getUnitIdsThatHaveAbilityOfName(const std::string& p_name);
	std::vector<int> getUnitIdsThatHaveTag(const std::string& p_tag);

	DeckData* getDeckDataFromId(const int& p_identifier);
	int getDeckDataListCount();
	void addNewDeckData(DeckData*);

	kitten::K_GameObject* attachCustomComponentsToGameObject(const int& p_identifier, kitten::K_GameObject* p_targetGameObject);
	unit::Unit* getUnitInstanceFromId(const int& p_identifier);
	bool checkIfComponentDriven(const int& p_identifier);

	// ===----- For internal Use Only after this comment ---------------------------------------------------

	void setupDatabank();
	void destroyDatabank();
	// returns an empty ability if none is found matching string, adds it internally to a late load list. 
	// To be used only within kibble
	unit::AbilityDescription* getCopyAbilityFromName(const std::string& p_name);
	void flagAbilityForLateLoad(unit::AbilityDescription*);
}