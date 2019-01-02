#include "UI\CardArt.h"

namespace userinterface
{
	CardArt::CardArt(const std::string p_pathToArt) 
	{

	}
	CardArt::~CardArt()
	{
	
	}

	void CardArt::setArt(const std::string p_pathToArt)
	{
		m_cardArt = p_pathToArt;
	}

	std::string CardArt::getArt()
	{
		return m_cardArt;
	}
}