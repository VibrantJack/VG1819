#include "UnitDataType.hpp"
#include <string>

unit::UnitData* getUnitDataFrom(nlohmann::json& p_jsonfile) {
	std::string name;
	int hp, mv, in, cost;
	unit::UnitSize size = unit::UnitSize::cube;
	std::vector<std::string> tags, ad, sd;

	name = p_jsonfile["name"].get<std::string>();
	hp = p_jsonfile["hp"];
	mv = p_jsonfile["mv"];
	in = p_jsonfile["in"];
	cost = p_jsonfile["cost"];
	if (p_jsonfile.find("size") != p_jsonfile.end()) {
		if (p_jsonfile["size"] == "cube")
			size = unit::UnitSize::cube;
		else
			size = unit::UnitSize::point;
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

	unit::UnitData* ud = new unit::UnitData();
	ud->m_name = name;
	ud->m_HP = hp;
	ud->m_MV = mv;
	ud->m_IN = in;
	ud->m_Cost = cost;
	ud->m_size = size;
	ud->m_tags = tags;

	ud->m_ad = ad;
	ud->m_sd = sd;

	//ud->m_texPath;
	//ud->m_porPath;

	return ud;
}

std::vector<unit::UnitData*> getMultipleUnitDataFrom(nlohmann::json& p_jsonfile) {
	assert(p_jsonfile["units"].is_array());
	std::vector<unit::UnitData*> units;
	for (nlohmann::json::iterator it = p_jsonfile["units"].begin(); it != p_jsonfile["units"].end(); ++it) {
		units.push_back(getUnitDataFrom(*it));
	}

	return units;
}