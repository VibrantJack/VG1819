#pragma once
#include "kitten/K_Component.h"
#include "DeckData.hpp"
class DeckInitializingComponent : public kitten::K_Component 
{
private:
	DeckData* m_source;
	int m_playerId;
public:
	static DeckInitializingComponent* getActiveInstance();

	void setDeckData(DeckData* p_source) { m_source = p_source; }
	void setPlayerId(int p_playerId) { m_playerId = p_playerId; }

	const DeckData* getDeckData() const;
	const int getPlayerId() const;

	DeckInitializingComponent();
	~DeckInitializingComponent();
};