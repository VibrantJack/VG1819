#pragma once
#include <vector>
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
		int m_power;//abilities power can be changed, so it must send the current power
		int m_counterNumber;//some abilities influenced by some counters
	};
}
