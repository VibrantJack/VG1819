#pragma once
#include "UnitCommon.h"

//Rock

namespace unit
{
	class UnitData
	{
	public:
		UnitData();
		UnitData(std::string p_name, int p_HP, int p_MV, int p_IN, int p_Cost, UnitSize p_size,
			std::vector<std::string> p_tags, std::vector<std::string> p_AD, std::vector<std::string> p_SD);
		~UnitData();

		//get method for member
		std::string getName() { return m_name; };
		int getHP() { return m_HP; };
		int getMV() { return m_MV; };
		int getIN() { return m_IN; };
		int getCost() { return m_Cost; };
		UnitSize getSize() { return m_size; };
		std::vector<std::string>* getTags() { return &m_tags; };
		std::vector<std::string>* getAbility() { return &m_abilityDescription; };
		std::vector<std::string>* getStatus() { return &m_statusDescription; };

	private:
		//all member below can only be read but not changed

		std::string m_name;
		int m_HP;
		int m_MV;
		int m_IN;
		int m_Cost;
		UnitSize m_size; // size is enum

		std::vector<std::string> m_tags;//commander and other useful things

										//we need name to find ability and status
		std::vector<std::string> m_abilityDescription;
		std::vector<std::string> m_statusDescription;

	};
}


