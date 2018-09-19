#include "UnitDataType.hpp"
#include <string>

UnitData* getUnitDataFrom(nlohmann::json& jsonfile) {
	std::string name;
	int hp, mv, in, cost;
	UnitSize size = UnitSize::cube;
	std::vector<std::string> tags, ad, sd;

	name = jsonfile["name"].get<std::string>();
	hp = jsonfile["hp"];
	mv = jsonfile["mv"];
	in = jsonfile["in"];
	cost = jsonfile["cost"];
	if (jsonfile.find("size") != jsonfile.end()) {
		if (jsonfile["size"] == "cube")
			size = UnitSize::cube;
		else
			size = UnitSize::point;
	}

	if (jsonfile.find("tags") != jsonfile.end()) {
		assert(jsonfile["tags"].is_array());
		for (nlohmann::json::iterator it = jsonfile["tags"].begin(); it != jsonfile["tags"].end(); ++it) {
			tags.push_back(*it);
		}
	}

	if (jsonfile.find("ad") != jsonfile.end()) {
		assert(jsonfile["ad"].is_array());
		for (nlohmann::json::iterator it = jsonfile["ad"].begin(); it != jsonfile["ad"].end(); ++it) {
			ad.push_back(*it);
		}
	}

	if (jsonfile.find("sd") != jsonfile.end()) {
		assert(jsonfile["sd"].is_array());
		for (nlohmann::json::iterator it = jsonfile["sd"].begin(); it != jsonfile["sd"].end(); ++it) {
			sd.push_back(*it);
		}
	}

	return new UnitData(name, hp, mv, in, cost, size, tags, ad, sd);
}

std::vector<UnitData*> getMultipleUnitDataFrom(nlohmann::json& jsonfile) {
	assert(jsonfile["units"].is_array());
	std::vector<UnitData*> units;
	for (nlohmann::json::iterator it = jsonfile["units"].begin(); it != jsonfile["units"].end(); ++it) {
		units.push_back(getUnitDataFrom(*it));
	}

	return units;
}