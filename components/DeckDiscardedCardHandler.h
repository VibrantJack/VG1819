#pragma once

#include "kitten/K_Component.h"
#include "kitten/event_system/EventManager.h"
#include "_Project/LerpController.h"

class DeckDiscardedCardHandler : public kitten::K_Component, public LerpController::PositionLerpFinishedCallback
{
protected:
	kitten::K_GameObject* card;

	void onEnabled() override;
	void onDisabled() override;
public:
	DeckDiscardedCardHandler();
	~DeckDiscardedCardHandler();

	void receiveDiscardedCard(kitten::Event::EventType p_type, kitten::Event* p_event);

	void start() override;

	void onPositionLerpFinished() override;
};