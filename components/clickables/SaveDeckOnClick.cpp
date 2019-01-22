#include "SaveDeckOnClick.h"
#include "components/DeckAlterationComponent.h"
#include "components/DisplayFrame/CommanderDisplayFrame.h"
#include "kibble/databank/databank.hpp"

SaveDeckOnClick::SaveDeckOnClick() { 
	m_text = "Wanna save changes my dude?";
}

SaveDeckOnClick::~SaveDeckOnClick() {

}

void SaveDeckOnClick::onSuccess()
{
	DeckAlterationComponent::getActiveInstance()->saveDeck();
	PromptPopUp::getActiveInstance()->setEnabledPrompt(false);
}

void SaveDeckOnClick::onClick()
{
	PromptPopUp::getActiveInstance()->setBehavior(this);
}