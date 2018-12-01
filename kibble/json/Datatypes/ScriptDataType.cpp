#include "json.hpp"

#define JSONHAS(str) p_jsonFile->find(str) != p_jsonFile->end()
#define LOOKUP(str) p_jsonFile->operator[](str)
#define SET(varName,jsonName) varName = p_jsonFile->operator[](jsonName)
#define SETOPT(varName,jsonName) if(JSONHAS(jsonName)) SET(varName,jsonName)
#define SETOPTDEF(varName,jsonName,defaultVal) if(JSONHAS(jsonName)) SET(varName,jsonName); else varName = defaultVal

#include "unit/InitiativeTracker/InitiativeTracker.h"
void startInitiativeTrackerTurn(nlohmann::json* p_jsonFile) {
	unit::InitiativeTracker::getInstance()->gameTurnStart();
}

void setupInitiativeTracker(nlohmann::json* p_jsonFile) {
	unit::InitiativeTracker::createInstance();
}

#include "unit/UnitMonitor.h"
void printSpawnedUnits(nlohmann::json* p_jsonFile) {
	unit::UnitMonitor::getInstance()->printIT();
}

#include "UI/HandFrame.h"
void makeAHand(nlohmann::json* p_jsonFile) {
	userinterface::HandFrame::makeAHand();
}

#include "unit/UnitSpawn.h"
#include "unit/unitComponent/UnitMove.h"
void spawnUnit(nlohmann::json* p_jsonFile) {
	int unitId, tileX, tileY;

	SET(unitId, "unit");
	tileX = LOOKUP("tile2d")[0];
	tileY = LOOKUP("tile2d")[1];

	unit::UnitSpawn::getInstanceSafe()->spawnUnitObject(unitId)
		->getComponent<unit::UnitMove>()->setTile(tileX, tileY);
}

#include <map>
#include "ScriptDataType.h"

std::map<std::string, void (*)(nlohmann::json* p_jsonFile)> scriptMap;
void setupScriptMap() {
	scriptMap["SpawnUnit"]=&spawnUnit;
	scriptMap["startInitiativeTrackerTurn"]=&startInitiativeTrackerTurn;
	scriptMap["printSpawnedUnits"]=&printSpawnedUnits;
	scriptMap["setupInitiativeTracker"]=&setupInitiativeTracker;
	scriptMap["makeAHand"]=&makeAHand;

}

void runRelatedScript(nlohmann::json* p_jsonFile) {
	std::string key = p_jsonFile->operator[]("name");
	if (scriptMap.find(key) != scriptMap.end()) {
		scriptMap[key](p_jsonFile);
	}
}
