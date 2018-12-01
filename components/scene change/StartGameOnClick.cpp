#include "StartGameOnClick.h"
#include "kitten/K_Instance.h"
#include "kitten/K_GameObjectManager.h"
#include "components/DeckInitializingComponent.h"
#include "components/DecksDisplayFrame.h"
#include "kibble/databank/databank.hpp"

void StartGameOnClick::onClick() 
{
	// Add All canceling components here
	if (DecksDisplayFrame::getActiveInstance()->getCurrentPickedDeckId() < 0) return;

	// --------------------------
	kitten::K_GameObject * survivor = kitten::K_GameObjectManager::getInstance()->createNewGameObject("newgame_survivor.json");

	// ADD ALL INFORMATION COMPONENTS ON SURVIVOR
	DeckInitializingComponent* deckInitComponent = survivor->getComponent<DeckInitializingComponent>();
	deckInitComponent->setDeckData(kibble::getDeckDataFromId(DecksDisplayFrame::getActiveInstance()->getCurrentPickedDeckId()));
	deckInitComponent->setPlayerId(1);

	// --------------------------
	kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(survivor);
	kitten::K_Instance::changeScene("mainscene.txt");
}