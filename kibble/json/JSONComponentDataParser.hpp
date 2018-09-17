#pragma once
#include "kibble/ComponentDataParser.hpp"
#include "jsonextra.hpp"
#include <map>
#include <string>

namespace kibble {
	class JSONComponentDataParser : public kibble::ComponentDataParser {
		nlohmann::json* m_jsonfile;
	public:
		kitten::K_Component* getComponentInternally();
		JSONComponentDataParser(nlohmann::json* jsonfile);
	};
}