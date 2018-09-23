#pragma once
#include "UnitCommon.h"

//Rock

namespace unit
{
	class UnitData
	{
	public:
		UnitData();
		~UnitData();

		std::string m_name;
		int m_HP;
		int m_MV;
		int m_IN;
		int m_Cost;
		UnitSize m_size; // size is enum

		//Commander and other useful things, commander must be first, in [0], 
		std::vector<std::string> m_tags;

		std::vector<std::string> m_ad;
		std::vector<std::string> m_sd;

		std::string m_texPath;
		std::string m_porPath;
	};
}


