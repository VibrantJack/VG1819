#pragma once
#include <string>
#include "kitten\K_Component.h"

namespace userinterface{
	class CardArt : public kitten::K_Component
	{
	public:
		CardArt(const std::string p_pathToArt);
		~CardArt();

		void setArt(const std::string p_pathToArt);
		std::string getArt();
		
	private:
		std::string m_pathToArt;
	};
};

