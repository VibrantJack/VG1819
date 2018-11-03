#pragma once

#include "UIObject.h"

//austin's UI Object

namespace userinterface
{
	class HandFrame;

	class CardUIO : public UIObject
	{

	public:
		CardUIO(const char* p_pathToTex);
		~CardUIO();

		void returnToHand();
		void scaleAsCard();
		void assignParentHand(HandFrame* p_toAssign);

	private:
		HandFrame* m_parentHand;

	};
		
}