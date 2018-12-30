#include "UnitDisplayFrame.h"
#include "kitten/K_GameObjectManager.h"
#include "kibble/databank/databank.hpp"
#include "puppy/Text/TextBox.h"
#include <math.h>
#include "components/DeckInitializingComponent.h"
#include <string>
#include "unit/Unit.h"

UnitDisplayFrame* instance;
UnitDisplayFrame* UnitDisplayFrame::getActiveInstance() { return instance; }

UnitDisplayFrame::UnitDisplayFrame(int p_marginX, int p_marginY) : m_unitVector(kibble::getNonCommanderIds()), DisplayFrame(p_marginX, p_marginY,
	std::string("Deck/unit-display_frame_object.json"),
	std::string("Deck/deck_display-left_button.json"), std::string("Deck/deck_display-right_button.json"),
	std::string("Deck/deck_display-highlight.json"), std::string("Deck/deck-display_empty.json"))// TODO add an empty object
{
	instance = this;
}

UnitDisplayFrame::~UnitDisplayFrame()
{
	instance = nullptr;

}

void UnitDisplayFrame::start()
{
	m_currentPick = -1;
	DisplayFrame::start();
}


int UnitDisplayFrame::getTargetAvailable() {
	return m_unitVector.size();
}

void UnitDisplayFrame::updateIndividualDisplayObject(int p_activeObjectIndex)
{
	//+ m_currentSet * m_objectsToDisplay.size() To get the deck id 
	unit::Unit* unitData = kibble::getUnitFromId(m_unitVector[p_activeObjectIndex + m_currentSet * m_objectsToDisplay.size()]);

	// Set commander name. The components are in the order loaded in the file
	m_objectsToDisplay[p_activeObjectIndex]->getTransform().getChildren()[2]->getAttachedGameObject() // Third is the TextBox
		.getComponent<puppy::TextBox>()->setText(unitData->m_name);

	// Add picture later TODO
}
