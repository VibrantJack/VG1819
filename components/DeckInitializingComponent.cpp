#include "DeckInitializingComponent.h"

DeckInitializingComponent* instance = nullptr;


DeckInitializingComponent::DeckInitializingComponent() : m_source(nullptr)
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

void DeckInitializingComponent::setDeckData(DeckData* p_source)
{
	m_source = p_source;
	toggleMessage(false);
}

const DeckData* DeckInitializingComponent::getDeckData() const
{
	return m_source;
}
const int DeckInitializingComponent::getPlayerId() const
{
	return m_playerId;
}

void DeckInitializingComponent::start()
{
	m_selectMessage = kitten::K_GameObjectManager::getInstance()->createNewGameObject("select_deck_message.json");
	kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(m_selectMessage);

	m_selectMessage->setEnabled(false);
}

void DeckInitializingComponent::toggleMessage(bool p_enable)
{
	m_selectMessage->setEnabled(p_enable);
}