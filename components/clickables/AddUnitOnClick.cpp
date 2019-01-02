#include "AddUnitOnClick.h"
#include "components/DeckAlterationComponent.h"
#include "components/DisplayFrame/UnitDisplayFrame.h"
#include "components/DisplayFrame/DeckUnitsDisplayFrame.h"
#include "kibble/databank/databank.hpp"

AddUnitOnClick::AddUnitOnClick(){ }

AddUnitOnClick::~AddUnitOnClick() {

}

void AddUnitOnClick::onClick()
{
	// This Component assumes that the object it's going to be attached to is going to be part of the display Frame object.
	int unit = UnitDisplayFrame::getActiveInstance()->getUnitTiedTo(&this->m_attachedObject->getTransform().getParent()->getAttachedGameObject());
	DeckData* temp = DeckAlterationComponent::getActiveInstance()->getDeckData();

	auto iter = temp->cards.begin();
	for (; iter != temp->cards.end(); ++iter)
	{
		if (iter->first == unit)
		{
			iter->second++;
			break;
		}
	}

	if (iter == temp->cards.end())
	{
		temp->cards.push_back({ unit, 1 });
	}

	DeckUnitsDisplayFrame::getActiveInstance()->updateDisplay();
}