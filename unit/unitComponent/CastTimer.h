#pragma once

#include "unit/UnitCommon.h"
#include <unordered_map>

//Rock
//This class will record ability's cd

namespace unit
{
	class CastTimer
	{
	public:
		CastTimer(Unit* p_unit);
		~CastTimer();

		bool isCasting();
		std::vector<kitten::K_GameObject*> getTarget();
		void set(std::string p_abilityName, ability::AbilityInfoPackage* p_pack, int p_timer);
		int changeTimer(int p_n = -1);
		void cancelCast();
		void cast();

	private:
		ability::AbilityInfoPackage* m_pack;
		std::string m_abilityName;
		int m_timer;
		bool m_cast;

		kitten::K_GameObject* m_timerSymbol;
		Unit* m_unit;

	};
}