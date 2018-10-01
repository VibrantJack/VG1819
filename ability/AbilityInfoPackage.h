#pragma once
#include <vector>
#include <map>
//Rock
//This is the package that will be delivered through ability system
//It will contain all and may be surplus information

namespace unit
{
	class Unit;
}

namespace ability
{
	class AbilityInfoPackage
	{
	public:
		unit::Unit * m_source;//the unit who uses the ability
		unit::Unit * m_target;//the single unit who will be effected
		std::vector<unit::Unit*> m_multipleTargets;//the list of units who will be effected, used for area ability
		std::map<std::string, int> m_intValue;
	};
}
