#include "jsonextra.hpp"
#include "JSONUnitDataParser.hpp"
#include "Datatypes/UnitDataType.hpp"
#include "Datatypes/ComponentDataType.hpp"

constexpr auto UNIT_DIRECTORY = "data/unit/";

kibble::UnitFileStruct kibble::JSONUnitDataParser::getUnit(const std::string& p_filename) {
	nlohmann::json jsonfile = jsonIn(UNIT_DIRECTORY + p_filename);
	kibble::UnitFileStruct result;

	if (jsonfile.find("unit") != jsonfile.end()) {
		result.data = getUnitDataFrom(jsonfile["unit"]);
		for (nlohmann::json::iterator it = jsonfile["components"].begin(); it != jsonfile["components"].end(); ++it) {
			result.components.push_back(*it);
		}
		if (jsonfile.find("translate") != jsonfile.end()) {
			result.translate[0] = jsonfile["translate"][0];
			result.translate[1] = jsonfile["translate"][1];
			result.translate[2] = jsonfile["translate"][2];
		}

		if (jsonfile.find("rotate") != jsonfile.end()) {
			result.rotate[0] = jsonfile["rotate"][0];
			result.rotate[1] = jsonfile["rotate"][1];
			result.rotate[2] = jsonfile["rotate"][2];
		}

		if (jsonfile.find("scale") != jsonfile.end()) {
			result.scale[0] = jsonfile["scale"][0];
			result.scale[1] = jsonfile["scale"][1];
			result.scale[2] = jsonfile["scale"][2];
		}
	}
	else
	{
		result.data = getUnitDataFrom(jsonfile);
	}

	return result;
}