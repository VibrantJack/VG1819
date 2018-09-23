#pragma once
#include <string>
#include <map>

//Rock

//This class will contain a list of information of an ability
//It attached to a unit and will be used when the unit assemble an ability info package

namespace unit
{
	class AbilityDescription
	{
	public:
		std::map<std::string, std::string> m_stringValue;
		std::map<std::string, int> m_intValue;


	};
}