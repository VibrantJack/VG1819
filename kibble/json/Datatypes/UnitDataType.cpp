#include "UnitDataType.hpp"
#include <string>

UnitData* getUnitDataFrom(nlohmann::json& p_jsonfile) {
	std::string name;
	int hp, mv, in, cost;
	UnitSize size = UnitSize::cube;
	std::vector<std::string> tags, ad, sd;

	name = p_jsonfile["name"].get<std::string>();
	hp = p_jsonfile["hp"];
	mv = p_jsonfile["mv"];
	in = p_jsonfile["in"];
	cost = p_jsonfile["cost"];
	if (p_jsonfile.find("size") != p_jsonfile.end()) {
		if (p_jsonfile["size"] == "cube")
			size = UnitSize::cube;
		else
			size = UnitSize::point;
	}

	if (p_jsonfile.find("tags") != p_jsonfile.end()) {
		assert(p_jsonfile["tags"].is_array());
		for (nlohmann::json::iterator it = p_jsonfile["tags"].begin(); it != p_jsonfile["tags"].end(); ++it) {
			tags.push_back(*it);
		}
	}

	if (p_jsonfile.find("ad") != p_jsonfile.end()) {
		assert(p_jsonfile["ad"].is_array());
		for (nlohmann::json::iterator it = p_jsonfile["ad"].begin(); it != p_jsonfile["ad"].end(); ++it) {
			ad.push_back(*it);
		}
	}

	if (p_jsonfile.find("sd") != p_jsonfile.end()) {
		assert(p_jsonfile["sd"].is_array());
		for (nlohmann::json::iterator it = p_jsonfile["sd"].begin(); it != p_jsonfile["sd"].end(); ++it) {
			sd.push_back(*it);
		}
	}

	return new UnitData(name, hp, mv, in, cost, size, tags, ad, sd);
}

std::vector<UnitData*> getMultipleUnitDataFrom(nlohmann::json& p_jsonfile) {
	assert(p_jsonfile["units"].is_array());
	std::vector<UnitData*> units;
	for (nlohmann::json::iterator it = p_jsonfile["units"].begin(); it != p_jsonfile["units"].end(); ++it) {
		units.push_back(getUnitDataFrom(*it));
	}

	return units;
}