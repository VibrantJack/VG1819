#include "DiscardDeckOnClick.h"
#include "components/DeckAlterationComponent.h"
#include "kitten/K_Instance.h"

DiscardDeckOnClick::DiscardDeckOnClick() { }

DiscardDeckOnClick::~DiscardDeckOnClick() {

}

void DiscardDeckOnClick::onClick()
{
	DeckAlterationComponent::getActiveInstance()->discardChanges();
	kitten::K_Instance::changeScene("mainmenu.json");
}