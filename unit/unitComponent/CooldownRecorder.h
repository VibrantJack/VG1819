#pragma once

#include "unit/UnitCommon.h"
#include <unordered_map>

//Rock
//This class will record ability's cd

namespace unit
{
	class CooldownRecorder
	{
	private:
		std::unordered_map<AbilityDescription*, int> m_cdmap;

	public:
		CooldownRecorder();
		~CooldownRecorder();

		void addCD(AbilityDescription* p_ad);
		void cancelCD(AbilityDescription* p_ad);
		int checkCD(AbilityDescription* p_ad);
		void changeCDByEffect(AbilityDescription* p_ad, int p_cd);

		void reduceCD();
	};
}