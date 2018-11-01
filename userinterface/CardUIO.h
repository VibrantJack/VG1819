#pragma once

#include "UIObject.h"

namespace userinterface
{
	class HandFrame;

	class CardUIO : public UIObject
	{

	public:
		CardUIO(const char* p_pathToTex);
		~CardUIO();

		void returnToHand();

	private:
		HandFrame* m_parentHand;

	};
		
}