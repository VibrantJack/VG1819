#pragma once

#include "UIFrame.h"

namespace userinterface
{
	class CardUIO;

	class HandFrame : public UIFrame
	{
	public:
		HandFrame(const char* p_pathToTex);
		~HandFrame();

		void addCardToEnd(UIObject* p_cardToAdd);
		void addCardToFront(UIObject* p_cardToAdd);
		void removeCard(UIObject* p_cardToARemove);

		void reorderAllCards();

	private:
		

	};
}
