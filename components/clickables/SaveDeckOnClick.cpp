#include "SaveDeckOnClick.h"
#include "components/DeckAlterationComponent.h"
#include "components/DisplayFrame/CommanderDisplayFrame.h"
#include "kibble/databank/databank.hpp"

SaveDeckOnClick::SaveDeckOnClick() { }

SaveDeckOnClick::~SaveDeckOnClick() {

}

void SaveDeckOnClick::onClick()
{
	DeckAlterationComponent::getActiveInstance()->saveDeck();
}