#include "CardUIO.h"

namespace userinterface
{
	CardUIO::CardUIO(const char* p_pathToTex) : UIObject(p_pathToTex)
	{
		//nothing extra to add
	}

	CardUIO::~CardUIO()
	{

	}

	void CardUIO::scaleAsCard()
	{
		getTransform().scale2D(0.1, 0.25);
	}


	void CardUIO::assignParentHand(HandFrame* p_toAssign)
	{
		m_parentHand = p_toAssign;
	}

	void CardUIO::returnToHand()
	{
		
	}

}