#include "databank.hpp"

std::vector<unit::UnitData*> unitDataVector;

void kibble::destroyDatabank() {
	for (unit::UnitData* unit : unitDataVector) {
		delete unit;
	}
}

#include "kibble/kibble.hpp"
#include <fstream>
void kibble::setupDatabank() {
	unitDataVector.reserve(50);
	kibble::UnitDataParser* unitDataParser = kibble::getUnitDataParserInstance();
	
	std::ifstream input("data/gameunitlist.txt");
	if (input.is_open()) {
		std::string unitFilename;
		while (input >> unitFilename) {
			std::vector<unit::UnitData*> target = unitDataParser->getUnitList(unitFilename);
			unitDataVector.insert(unitDataVector.end(), target.begin(), target.end());
		}
	}
	else {
		throw std::exception("Something went wrong, file can't be opened."); // check if filename is correct.
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