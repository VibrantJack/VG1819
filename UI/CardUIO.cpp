#include "ui/CardUIO.h"

namespace userinterface
{
	CardUIO::CardUIO(const char* p_pathToTex) : UIObject(p_pathToTex)
	{
		//nothing new to add
	}

	CardUIO::~CardUIO()
	{

	}

	void CardUIO::scaleAsCard()
	{
		getTransform().scale2D(100, 170);
	}


	void CardUIO::assignParentHand(HandFrame* p_toAssign)
	{
		m_parentHand = p_toAssign;
	}

	void CardUIO::returnToHand()
	{
		
	}

}