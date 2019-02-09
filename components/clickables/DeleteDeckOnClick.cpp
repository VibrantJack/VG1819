#include "DeleteDeckOnClick.h"
#include "components/DeckAlterationComponent.h"
#include "components/DecksDisplayFrame.h"
#include "kibble/databank/databank.hpp"
#include "_Project/DisableAfterTime.h"

DeleteDeckOnClick::DeleteDeckOnClick() { }

DeleteDeckOnClick::~DeleteDeckOnClick() {

}

void DeleteDeckOnClick::onSuccess()
{
	int deckId = DecksDisplayFrame::getActiveInstance()->getCurrentPickedDeckId();
	kibble::eraseDeckData(deckId);
	DecksDisplayFrame::getActiveInstance()->updateDisplay();
	PromptPopUp::getActiveInstance()->setEnabledPrompt(false);

	if (m_message == nullptr)
	{
		m_message = kitten::K_GameObjectManager::getInstance()->createNewGameObject("deleted_deck_message.json");
	}
	else
	{
		m_message->setEnabled(true);
	}
	m_message->getComponent<DisableAfterTime>()->setTime(3.0);
}

void DeleteDeckOnClick::onClick()
{
	m_text = "Are you sure you want to delete this deck there, buddy?";
	PromptPopUp::getActiveInstance()->setEnabledPrompt(true);
	PromptPopUp::getActiveInstance()->setBehavior(this);
}