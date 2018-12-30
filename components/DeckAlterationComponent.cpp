#include "DeckAlterationComponent.h"
#include "kibble/databank/databank.hpp"

DeckAlterationComponent* instance = nullptr;


DeckAlterationComponent::DeckAlterationComponent() : m_source(nullptr)
{
	instance = this;

}

DeckAlterationComponent::~DeckAlterationComponent()
{
	instance = nullptr;
	if (m_saved == false) delete m_source;
}

DeckAlterationComponent * DeckAlterationComponent::getActiveInstance()
{
	return instance;
}

// Copies data, remember that this deletes old one. 
void DeckAlterationComponent::copyDeckData(const DeckData* p_source)
{
	if(m_saved == false) delete m_source;
	m_source = new DeckData(*p_source);

}

DeckData* DeckAlterationComponent::getDeckData()
{
	return m_source;
}

void DeckAlterationComponent::saveDeck()
{
	if (m_deckId < 0 || m_source == nullptr) assert(false); // there is no deck chosen to alter
	kibble::replaceDeckData(m_deckId,m_source);
	m_saved = true;
}

void DeckAlterationComponent::discardChanges()
{
	if(m_saved == false) delete m_source;
	m_source = nullptr;
	m_deckId = -1;
	m_saved = false;
} 