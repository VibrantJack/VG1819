#pragma once

#include "kitten\event_system\EventManager.h"
#include "kitten\K_Component.h"
#include "DeckData.hpp"

class DeckComponent : public kitten::K_Component
{
	const DeckData* m_deckSource;
	std::vector<int> m_cardPool;
	int m_playerID;

	void shuffleEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data);
	void discardEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data);
	void drawEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data);
	void peekEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data);
	void addEventReceiver(kitten::Event::EventType p_type, kitten::Event* p_data);
	void onDisabled();
	void onEnabled();

	//put specific cards to hand without changing deck
	void putCardToHand(kitten::Event::EventType p_type, kitten::Event * p_data);
public:
	DeckComponent(){}
	~DeckComponent();

	void start() override;

	void shuffle();
	void draw(int p_topNum= 1);
	void discard(int p_topNum = 1);
	void addTop(int p_cardIndex);
	void peek(int p_topNum = 1);
	void informEmptyDeck();
};