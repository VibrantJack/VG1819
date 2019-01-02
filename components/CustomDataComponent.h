#pragma once
#include "kitten/K_Component.h"
#include <map>
#include <string>

class CustomDataComponent : public kitten::K_Component
{
public:
	std::map<std::string, std::string> m_stringMap;
	std::map<std::string, float> m_floatMap;
	std::map<std::string, int> m_intMap;
	std::map<std::string, bool> m_boolMap;
};