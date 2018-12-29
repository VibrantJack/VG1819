#pragma once
#include "kitten/K_Component.h"
#include "DeckData.hpp"
#include "kitten\K_GameObjectManager.h"

class DeckInitializingComponent : public kitten::K_Component 
{
private:
	DeckData* m_source;
	int m_deckId;
	int m_playerId;

	kitten::K_GameObject* m_selectMessage;
public:
	static DeckInitializingComponent* getActiveInstance();

	void setDeckData(DeckData* p_source);
	void setDeckId(int p_id) { m_deckId = p_id; }
	void setPlayerId(int p_playerId) { m_playerId = p_playerId; }

	const DeckData* getDeckData() const;
	const int getDeckId() const { return m_deckId; }
	const int getPlayerId() const;

	DeckInitializingComponent();
	~DeckInitializingComponent();

	virtual void start() override;

	void toggleMessage(bool p_enable);
};