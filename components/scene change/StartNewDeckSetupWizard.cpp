#include "StartNewDeckSetupWizard.h"
#include "components/DeckAlterationComponent.h"
#include "components/DeckInitializingComponent.h"
#include "kitten/InputManager.h"
#include "kibble/databank/databank.hpp"
#include "puppy/Text/TextBox.h"

void StartNewDeckSetupWizard::start()
{
	input::InputManager::getInstance()->setPollMode(false);
	m_stringInputDisplay = m_attachedObject->getComponent<StringInputDisplay>();
	assert(m_stringInputDisplay != nullptr);
}

StartNewDeckSetupWizard::StartNewDeckSetupWizard()
{

}

StartNewDeckSetupWizard::~StartNewDeckSetupWizard()
{

	std::string deckName = m_stringInputDisplay->getString();
	if(deckName == "") deckName = m_attachedObject->getComponent<puppy::TextBox>()->getText();

	DeckData* deckData = new DeckData();
	deckData->name = deckName;

	DeckAlterationComponent::getActiveInstance()->discardChanges();
	DeckAlterationComponent::getActiveInstance()->copyDeckData(deckData);
	input::InputManager::getInstance()->setPollMode(true);
}
