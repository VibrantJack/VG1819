#pragma once
#include "kitten/K_Component.h"
#include "DeckData.hpp"
class DeckInitializingComponent : public kitten::K_Component 
{
private:
	DeckData* m_source;
	int m_deckId;
	int m_playerId;
public:
	static DeckInitializingComponent* getActiveInstance();

	void setDeckData(DeckData* p_source) { m_source = p_source; }
	void setDeckId(int p_id) { m_deckId = p_id; }
	void setPlayerId(int p_playerId) { m_playerId = p_playerId; }

	const DeckData* getDeckData() const;
	const int getDeckId() const { return m_deckId; }
	const int getPlayerId() const;

	DeckInitializingComponent();
	~DeckInitializingComponent();
};