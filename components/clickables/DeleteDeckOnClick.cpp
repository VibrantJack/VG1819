#include "DeleteDeckOnClick.h"
#include "components/DeckAlterationComponent.h"
#include "components/DecksDisplayFrame.h"
#include "kibble/databank/databank.hpp"

DeleteDeckOnClick::DeleteDeckOnClick() { }

DeleteDeckOnClick::~DeleteDeckOnClick() {

}

void DeleteDeckOnClick::onClick()
{
	int deckId = DecksDisplayFrame::getActiveInstance()->getCurrentPickedDeckId();
	kibble::eraseDeckData(deckId);
	DecksDisplayFrame::getActiveInstance()->updateDisplay();
}