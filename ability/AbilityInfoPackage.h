#pragma once
#include "kitten/K_Common.h"
#include <vector>
#include <unordered_map>
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
		std::vector<unit::Unit*> m_targets;//the list of units who will be effected
		std::unordered_map<std::string, int> m_intValue;
		std::unordered_map<std::string, std::string> m_stringValue;
		
		// For passing which tiles are needed for the ability
		std::vector<std::pair<int, int>> m_targetTilesPos;
		std::vector<kitten::K_GameObject*> m_targetTilesGO;

		// Source ClientID, for networking
		int m_sourceClientId;

		//special pointer, for summonning
		kitten::K_GameObject* m_cardGOForUnitSummon = nullptr;

		AbilityInfoPackage() {};
		~AbilityInfoPackage() {};

	};
}
