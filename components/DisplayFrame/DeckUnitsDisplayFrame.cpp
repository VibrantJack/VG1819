#include "DeckUnitsDisplayFrame.h"
#include "kitten/K_GameObjectManager.h"
#include "kibble/databank/databank.hpp"
#include "puppy/Text/TextBox.h"
#include <math.h>
#include "components/DeckAlterationComponent.h"
#include <string>
#include "unit/Unit.h"

DeckUnitsDisplayFrame* instance;
DeckUnitsDisplayFrame* DeckUnitsDisplayFrame::getActiveInstance() { return instance; }

DeckUnitsDisplayFrame::DeckUnitsDisplayFrame(int p_marginX, int p_marginY) : DisplayFrame(p_marginX, p_marginY,
	std::string("Deck/deckunits-display_frame_object.json"),
	std::string("Deck/deckunits-display_left_button.json"), std::string("Deck/deckunits-display_right_button.json"),
	std::string("Deck/deckunits-display_highlight.json"), std::string("Deck/deck-display_empty.json"))// TODO add an empty object
{
	instance = this;
	this->m_arrowPlacement = 1;
}

DeckUnitsDisplayFrame::~DeckUnitsDisplayFrame()
{
	instance = nullptr;
}

void DeckUnitsDisplayFrame::start()
{
	m_currentPick = -1;
	if (DeckAlterationComponent::getActiveInstance() == nullptr ||
		DeckAlterationComponent::getActiveInstance()->getDeckData() == nullptr
		)
		assert(false); // how are you viewing this without a deck being up. 
	m_deckData = kibble::getDeckDataFromId(DeckAlterationComponent::getActiveInstance()->getDeckId()); // using deck ID because we want to alter the deck data. 
	DisplayFrame::start();
}


int DeckUnitsDisplayFrame::getTargetAvailable() {
	return m_deckData->cards.size();
}

void DeckUnitsDisplayFrame::updateIndividualDisplayObject(int p_activeObjectIndex)
{
	//+ m_currentSet * m_objectsToDisplay.size() To get the element in main array

	// Set deck name. The components are in the order loaded in the file
	m_objectsToDisplay[p_activeObjectIndex]->getTransform().getChildren()[1]->getAttachedGameObject() // 2nd is the TextBox for name
		.getComponent<puppy::TextBox>()->setText(kibble::getUnitFromId(m_deckData->cards[p_activeObjectIndex + m_currentSet * m_objectsToDisplay.size()].first)->m_name);

	m_objectsToDisplay[p_activeObjectIndex]->getTransform().getChildren()[3]->getAttachedGameObject() // 4th is the textbox for count
		.getComponent<puppy::TextBox>()->setText(std::to_string(m_deckData->cards[p_activeObjectIndex + m_currentSet * m_objectsToDisplay.size()].second));

	// Add picture later TODO
}
