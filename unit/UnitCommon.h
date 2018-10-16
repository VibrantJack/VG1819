#pragma once

#include "ability/AbilityManager.h"
#include "ability/AbilityInfoPackage.h"
#include "kitten/K_Common.h"
#include "unit/unitComponent/UnitGraphic.h"
//@Rock

namespace unit
{
	enum UnitSize
	{
		point,
		cube,
	};

	struct AbilityDescription
	{
		//may have:
		//name:string
		//power: int
		//targetNumber:int
		//range: int
		//lv:int
		std::unordered_map<std::string, std::string> m_stringValue;
		std::unordered_map<std::string, int> m_intValue;
	};

	struct StatusDescription
	{
		//may have:
		//tp:timePointEvent
		//name:string
		//duration:int
		//power:int
		//lv:int
		std::vector<ability::TimePointEvent> m_TPList;
		std::unordered_map<std::string, std::string> m_stringValue;
		std::unordered_map<std::string, int> m_intValue;
	};

	struct UnitData
	{
		std::string m_name;
		int m_HP;
		int m_MV;
		int m_IN;
		int m_Cost;
		UnitSize m_size; // size is enum

		//Commander and other useful things, commander must be first, in [0], 
		std::vector<std::string> m_tags;

		std::vector<unit::AbilityDescription*> m_ad;
		std::vector<unit::StatusDescription*> m_sd;

		std::string m_texPath;
		std::string m_porPath;
	};
}

