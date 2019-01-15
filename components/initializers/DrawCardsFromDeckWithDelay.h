#pragma once
#include "kitten/K_Component.h"
#include "kitten/K_Time.h"

class DrawCardsFromDeckWithDelay : public kitten::K_Component
{
protected:
	unsigned int m_cardsDispensed = 0, m_cardsToDispense;
	float m_delayBetweenDraws, m_timeElapsed = 0; // Give this a negative number for a delay at the start. 
	kitten::K_Time* m_time = nullptr;

public:
	DrawCardsFromDeckWithDelay();
	~DrawCardsFromDeckWithDelay();

	static DrawCardsFromDeckWithDelay* getActiveInstance();

	void setCardCountToDispense(unsigned int p_count);
	void addDelayToStart(float p_timeToDelayBy) { m_timeElapsed -= p_timeToDelayBy; }
	void setDelayBetweenDraws(float p_timeToDelayBy) { m_delayBetweenDraws = p_timeToDelayBy; }

	void update() override;
	bool hasUpdate() const override { return true; }
	void start() override;

	void setupNetworkGame(kitten::Event::EventType p_type, kitten::Event* p_event);
};