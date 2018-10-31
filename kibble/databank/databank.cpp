#include "databank.hpp"
#include <map>
#include <set>

std::vector<unit::UnitData*> unitDataVector;
std::map<std::string, unit::AbilityDescription*> abilityDataMap;
std::map<std::string, std::vector<int>> abilityToUnitMap, tagToUnitMap;
std::set<unit::AbilityDescription*> lateLoadAbility;
std::vector<DeckData*> deckDataVector;

#define DECK_LIST "data/gamedecklist.txt"
#define UNIT_LIST "data/gameunitlist.txt"

// Basically the deconstructor
void kibble::destroyDatabank() {
	for (unit::UnitData* unit : unitDataVector) {
		for (unit::AbilityDescription* ability : unit->m_ad) {
			delete ability;
		}
		for (unit::StatusDescription* status : unit->m_sd) {
			delete status;
		}

		delete unit;
	}
	for (auto data : deckDataVector) {
		delete data;
	}
}

#include "kibble/kibble.hpp"
#include <fstream>
void kibble::setupDatabank() {
	unitDataVector.reserve(50);
	kibble::UnitDataParser* unitDataParser = kibble::getUnitDataParserInstance();

	std::ifstream input(UNIT_LIST);
	if (input.is_open()) {
		std::string unitFilename;
		while (input >> unitFilename) {
			std::vector<unit::UnitData*> target = unitDataParser->getUnitList(unitFilename);
			//unitDataVector.insert(unitDataVector.end(), target.begin(), target.end());
			for (unit::UnitData* unit : target) { // Go through all units
				for (unit::AbilityDescription* ability : unit->m_ad) { // Set up Abilities
					std::string name = ability->m_stringValue["name"];
					abilityToUnitMap[name].push_back(unitDataVector.size()); // add unit to list of units that use the ability
					if (abilityDataMap.find(name) == abilityDataMap.end()) { // check to see if a previous ability with the same name doesn't exist
						// if it finds nothing, it checks if it's being late loaded
						if(lateLoadAbility.find(ability) != lateLoadAbility.end())
							abilityDataMap[name] = ability; // if its not being loaded late set it
					}
				}

				for (std::string tag : unit->m_tags) { // Set up Tags
					tagToUnitMap[tag].push_back(unitDataVector.size());
				}

				// At the end push the unit into vector. 
				//This is left to the end so that previous calls to size return the actual index of this unit
				unitDataVector.push_back(unit);
			}
		}
		input.close();
	}
	else {
		throw std::exception("Something went wrong, can't open the Unit List file."); // check if filename is correct.
		return;
	}

	for (auto ability : lateLoadAbility) {// if an error is thrown back, most likely than not it's because it returned a nullptr. 
		unit::AbilityDescription* target = getAbilityFromName(ability->m_stringValue["basename"]);
		
		ability->m_intValue.insert(target->m_intValue.begin(), target->m_intValue.end());
		ability->m_stringValue.insert(target->m_stringValue.begin(), target->m_stringValue.end());
	}
	lateLoadAbility.clear();

	std::ifstream deckListFile(DECK_LIST);
	if (deckListFile.is_open()) {
		std::string deckFilename;
		while (deckListFile >> deckFilename) {
			deckDataVector.push_back(kibble::getDeckDataParserInstance()->getDeckData(deckFilename));
		}
		deckListFile.close();
	}
	else {
		throw std::exception("Something went wrong, can't open the deck List file."); // check if filename is correct.
		return;
	}
}


unit::UnitData* kibble::getUnitFromId(const int& p_identifier) {
	return unitDataVector[p_identifier];
}

std::vector<unit::UnitData*> kibble::getUnitsFromListOfIds(const std::vector<int>& p_identifiers) {
	std::vector<unit::UnitData*> unitList; 
	for (int index : p_identifiers) {
		unitList.push_back(unitDataVector[index]);
	}
	return unitList;
}


//returns null if none is found matching string
unit::AbilityDescription* kibble::getAbilityFromName(const std::string& p_name) {
	if (abilityDataMap.find(p_name) == abilityDataMap.end())
		return nullptr;
	else
		return abilityDataMap[p_name];
}

// returns an empty ability if none is found matching string it also internally adds it to late load list 
// otherwise it returns a copy of the ability to do whatever with. 
unit::AbilityDescription* kibble::getCopyAbilityFromName(const std::string& p_name) {
	if (abilityDataMap.find(p_name) == abilityDataMap.end()) {
		unit::AbilityDescription* ability = new unit::AbilityDescription();
		ability->m_stringValue["basename"] = p_name;
		ability->m_stringValue["name"] = p_name;
		lateLoadAbility.insert(ability);
		return ability;
	}
	else
		return new unit::AbilityDescription(*abilityDataMap[p_name]);
}
void kibble::flagAbilityForLateLoad(unit::AbilityDescription* p_ability) {
	lateLoadAbility.insert(p_ability);
}

std::vector<int> kibble::getUnitIdsThatHaveAbilityOfName(const std::string& p_name) {
	return abilityToUnitMap[p_name];
}
std::vector<int> kibble::getUnitIdsThatHaveTag(const std::string& p_tag) {
	return tagToUnitMap[p_tag];
}

int kibble::getDeckDataListCount() {
	return deckDataVector.size();
}

DeckData* kibble::getDeckDataFromId(const int& p_identifier) {
	return deckDataVector[p_identifier];
}

void kibble::addNewDeckData(DeckData* p_data) {
	kibble::getDeckDataParserInstance()->saveDeckData(p_data, "DeckNumbah" + std::to_string(deckDataVector.size()) + ".txt");
	std::ofstream deckList(DECK_LIST, std::ofstream::app | std::ofstream::out);
	if (deckList.is_open()) {
		deckList << std::endl << "DeckNumbah" + std::to_string(deckDataVector.size()) << ".txt" ;
	}
	deckDataVector.push_back(p_data);
}