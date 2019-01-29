#include "DecksDisplayFrame.h"
#include "kitten/K_GameObjectManager.h"
#include "kibble/databank/databank.hpp"
#include "puppy/Text/TextBox.h"
#include "UI/UIFrame.h"
#include "unit/Unit.h"
#include <math.h>
#include "DeckInitializingComponent.h"
#include <string>

DecksDisplayFrame* instance;
DecksDisplayFrame* DecksDisplayFrame::getActiveInstance() { return instance; }

DecksDisplayFrame::DecksDisplayFrame(int p_marginX, int p_marginY) : DisplayFrame(p_marginX, p_marginY,
	std::string("Deck/deck-display_frame_object.json"),
	std::string("Deck/deck_display-left_button.json"), std::string("Deck/deck_display-right_button.json"),
	std::string("Deck/deck_display-highlight.json"), std::string("Deck/deck-display_empty.json"))// TODO add an empty object
{
	instance = this;
}

DecksDisplayFrame::~DecksDisplayFrame()
{
	instance = nullptr;

}

void DecksDisplayFrame::start() 
{
	if (DeckInitializingComponent::getActiveInstance() != nullptr)
	{
		if (DeckInitializingComponent::getActiveInstance()->getDeckData() != nullptr)
		{
			m_currentPick = DeckInitializingComponent::getActiveInstance()->getDeckId();
		}
	}
	else
	{
		kitten::K_GameObject* survivor = kitten::K_GameObjectManager::getInstance()->createNewGameObject("Deck/deck-global_survivor.json");
		kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(survivor);
	}

	DisplayFrame::start();
}


void DecksDisplayFrame::onObjectClicked(int p_deckId)
{
	DeckInitializingComponent::getActiveInstance()->setDeckData(kibble::getDeckDataFromId(DecksDisplayFrame::getActiveInstance()->getCurrentPickedDeckId()));
	DeckInitializingComponent::getActiveInstance()->setDeckId(p_deckId);
	DeckInitializingComponent::getActiveInstance()->setPlayerId(0);
}

int DecksDisplayFrame::getTargetAvailable() {
	return kibble::getDeckDataListCount();
}

void DecksDisplayFrame::updateIndividualDisplayObject(int p_activeObjectIndex)
{
	//+ m_currentSet * m_objectsToDisplay.size() To get the deck id 
	DeckData* deck = kibble::getDeckDataFromId(p_activeObjectIndex + m_currentSet * m_objectsToDisplay.size());
	
	// Set deck name. The components are in the order loaded in the file
	m_objectsToDisplay[p_activeObjectIndex]->getTransform().getChildren()[2]->getAttachedGameObject() // Third is the TextBox
		.getComponent<puppy::TextBox>()->setText(deck->name);

	unit::Unit* commanderData = kibble::getUnitFromId(deck->commanderID);

	// Add picture 
	m_objectsToDisplay[p_activeObjectIndex]->getTransform().getChildren()[0]->getAttachedGameObject() // first is the ui frame
		.getComponent<userinterface::UIFrame>()->setTexture(commanderData->getPortraitTexturePath().c_str());
}
