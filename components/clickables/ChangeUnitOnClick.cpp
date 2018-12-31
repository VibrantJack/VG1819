#include "ChangeUnitOnClick.h"
#include "components/DeckAlterationComponent.h"
#include "components/DisplayFrame/DeckUnitsDisplayFrame.h"
#include "kibble/databank/databank.hpp"

ChangeUnitOnClick::ChangeUnitOnClick(bool p_increment) : m_increment(p_increment) { }

ChangeUnitOnClick::~ChangeUnitOnClick() {

}

void ChangeUnitOnClick::onClick()
{
	// This Component assumes that the object it's going to be attached to is going to be part of the display Frame object.
	int unit = DeckUnitsDisplayFrame::getActiveInstance()->getItemIndexTiedTo(&this->m_attachedObject->getTransform().getParent()->getAttachedGameObject());

	DeckData* temp = DeckAlterationComponent::getActiveInstance()->getDeckData();
	if (m_increment)
		temp->cards[unit].second += 1;
	else
		temp->cards[unit].second -= 1;

	if (temp->cards[unit].second <= 0)
	{
		temp->cards.erase(temp->cards.begin() + unit);
	}

	DeckUnitsDisplayFrame::getActiveInstance()->updateDisplay();
}