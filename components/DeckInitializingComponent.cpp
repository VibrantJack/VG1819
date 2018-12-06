#include "DeckInitializingComponent.h"

DeckInitializingComponent* instance = nullptr;


DeckInitializingComponent::DeckInitializingComponent()
{
	instance = this;
}

DeckInitializingComponent::~DeckInitializingComponent() 
{
	instance = nullptr;
}
DeckInitializingComponent * DeckInitializingComponent::getActiveInstance()
{
	return instance;
}

const DeckData* DeckInitializingComponent::getDeckData() const
{
	return m_source;
}
const int DeckInitializingComponent::getPlayerId() const
{
	return m_playerId;
}
