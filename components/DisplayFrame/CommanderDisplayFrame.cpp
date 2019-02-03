#include "CommanderDisplayFrame.h"
#include "kitten/K_GameObjectManager.h"
#include "kibble/databank/databank.hpp"
#include "puppy/Text/TextBox.h"
#include "components/DeckAlterationComponent.h"
#include "UI/UIFrame.h"
#include <math.h>
#include <string>
#include "unit/Unit.h"

CommanderDisplayFrame* instance;
CommanderDisplayFrame* CommanderDisplayFrame::getActiveInstance() { return instance; }

CommanderDisplayFrame::CommanderDisplayFrame(int p_marginX, int p_marginY) : m_commanderVector(kibble::getCommanderIds()), DisplayFrame(p_marginX, p_marginY,
	std::string("Deck/commander-display_frame_object.json"),
	std::string("Deck/deck_display-left_button.json"), std::string("Deck/deck_display-right_button.json"),
	std::string("Deck/commander-display_highlight.json"), std::string("Deck/general-display_empty.json"))// TODO add an empty object
{
	instance = this;
}

CommanderDisplayFrame::~CommanderDisplayFrame()
{
	instance = nullptr;
}

void CommanderDisplayFrame::start()
{
	if (DeckAlterationComponent::getActiveInstance() == nullptr
		|| DeckAlterationComponent::getActiveInstance()->getDeckData() == nullptr)
		assert(false); // What are you doing here if there's no commander to change. 

	m_commanderIndex = std::find(m_commanderVector.begin(), m_commanderVector.end(), 
		DeckAlterationComponent::getActiveInstance()->getDeckData()->commanderID) 
		- m_commanderVector.begin();
	m_currentPick = std::find(m_commanderVector.begin(), m_commanderVector.end(), 
		DeckAlterationComponent::getActiveInstance()->getDeckData()->commanderID)
		- m_commanderVector.begin(); // show which commander has been selected

	DisplayFrame::start();
}


int CommanderDisplayFrame::getTargetAvailable() {
	return m_commanderVector.size();
}

void CommanderDisplayFrame::updateIndividualDisplayObject(int p_activeObjectIndex)
{
	//+ m_currentSet * m_objectsToDisplay.size() To get the deck id 
	const unit::Unit* commanderData = kibble::getUnitFromId(m_commanderVector[p_activeObjectIndex + m_currentSet * m_objectsToDisplay.size()]);

	// Set commander name. The components are in the order loaded in the file
	m_objectsToDisplay[p_activeObjectIndex]->getTransform().getChildren()[2]->getAttachedGameObject() // Third is the TextBox
		.getComponent<puppy::TextBox>()->setText(commanderData->m_name);

	// Set if active
	m_objectsToDisplay[p_activeObjectIndex]->getTransform().getChildren()[3]->getAttachedGameObject() // 4th is the Clickable
		.getComponent<SetCommanderOnClick>()->setActive( // Not equal because we need to set it inactive if it is already chosen
			p_activeObjectIndex + m_currentSet * m_objectsToDisplay.size() != m_commanderIndex
		);

	// Add picture 
	m_objectsToDisplay[p_activeObjectIndex]->getTransform().getChildren()[0]->getAttachedGameObject() // first is the ui frame
		.getComponent<userinterface::UIFrame>()->setTexture(commanderData->getPortraitTexturePath().c_str());
}

void CommanderDisplayFrame::refreshCommander()
{
	m_commanderIndex = std::find(m_commanderVector.begin(),m_commanderVector.end(), DeckAlterationComponent::getActiveInstance()->getDeckData()->commanderID) - m_commanderVector.begin();
}

void CommanderDisplayFrame::refreshActiveButtons()
{
	for (int i = 0; i < m_currentActive; ++i)
	{
		m_objectsToDisplay[i]->getTransform().getChildren()[3]->getAttachedGameObject() // 4th is the Clickable
			.getComponent<SetCommanderOnClick>()->setActive( // Not equal because we need to set it inactive if it is already chosen
				i + m_currentSet * m_objectsToDisplay.size() != m_commanderIndex
			);
	}
}