#pragma once
#include "JSONComponentDataParser.hpp"
#include "kibble/json/Datatypes/ComponentDataType.hpp"

kitten::K_Component* kibble::JSONComponentDataParser::getComponentInternally() {
	std::string mapkey = this->m_jsonfile->operator[]("name");
	return getRelatedComponentBy(mapkey, m_jsonfile);
}

kibble::JSONComponentDataParser::JSONComponentDataParser(nlohmann::json* jsonfile) : m_jsonfile(jsonfile) {}