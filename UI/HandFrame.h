#pragma once

#include "UIFrame.h"
#include "kitten/event_system/EventManager.h"

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
		void setPlayerID(int p_playerId);

		void reorderAllCards();

		static void makeAHand();
		static HandFrame* getActiveInstance();

		virtual void start() override;
		virtual void onEnabled() override;
		virtual void onDisabled() override;

	private:
		
		int m_totalCards, m_playerID = 0;
		float m_cardX, m_cardY, m_padding, m_contentMargin;

		void receiveDrawnCard(kitten::Event::EventType p_type, kitten::Event* p_event);
	};
}
