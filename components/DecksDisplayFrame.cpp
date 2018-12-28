#include "DecksDisplayFrame.h"
#include "kitten/K_GameObjectManager.h"
#include "kibble/databank/databank.hpp"
#include "puppy/Text/TextBox.h"
#include <math.h>
#include "DeckInitializingComponent.h"
#include <string>

bool DecksDisplayFrame::sm_survivorFlagged = false;
DecksDisplayFrame* instance;
DecksDisplayFrame* DecksDisplayFrame::getActiveInstance() { return instance; }

DecksDisplayFrame::DecksDisplayFrame(int p_marginX, int p_marginY) : DisplayFrame(p_marginX, p_marginY,
	std::string("deck-display_frame_object.json"),
	std::string("deck_display-left_button.json"), std::string("deck_display-right_button.json"),
	std::string("deck_display-highlight.json"), std::string("deck_display-highlight.json"))// TODO add an empty object
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

	if (!sm_survivorFlagged)
	{
		kitten::K_GameObject * survivor = kitten::K_GameObjectManager::getInstance()->createNewGameObject("newgame_survivor.json");
		kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(survivor);
		sm_survivorFlagged = true;
	}

	DisplayFrame::start();
}


int DecksDisplayFrame::getTargetAvailable() {
	return kibble::getDeckDataListCount();
}

void DecksDisplayFrame::updateIndividualDisplayObject(int p_activeObjectIndex)
{
	m_objectsToDisplay[p_activeObjectIndex];
}
