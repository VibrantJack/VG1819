#include "UI\CardArt.h"

//austin
//holds the path to t
namespace userinterface
{
	CardArt::CardArt(const std::string p_pathToArt)
	{
		m_pathToArt = p_pathToArt;
	}

	CardArt::~CardArt()
	{}

	std::string CardArt::getArt()
	{
		return m_pathToArt;
	}

	void CardArt::setArt(const std::string p_pathToArt)
	{
		m_pathToArt = p_pathToArt;
	}
}