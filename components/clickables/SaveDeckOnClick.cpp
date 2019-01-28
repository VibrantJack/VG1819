#include "SaveDeckOnClick.h"
#include "components/DeckAlterationComponent.h"
#include "kitten/K_GameObjectManager.h"
#include "_Project/DisableAfterTime.h"

SaveDeckOnClick::SaveDeckOnClick() { 

}

SaveDeckOnClick::~SaveDeckOnClick() {

}

void SaveDeckOnClick::onClick()
{
	if (m_message == nullptr)
	{
		m_message = kitten::K_GameObjectManager::getInstance()->createNewGameObject("saved_deck_message.json");
	}
	else
	{
		m_message->setEnabled(true);
	}
	m_message->getComponent<DisableAfterTime>()->setTime(3.0);

	DeckAlterationComponent::getActiveInstance()->saveDeck();

}