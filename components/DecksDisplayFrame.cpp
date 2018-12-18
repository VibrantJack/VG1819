#include "DecksDisplayFrame.h"
#include "kitten/K_GameObjectManager.h"
#include "kibble/databank/databank.hpp"
#include "puppy/Text/TextBox.h"
#include <math.h>

bool DecksDisplayFrame::sm_survivorFlagged = false;
DecksDisplayFrame* instance;
DecksDisplayFrame* DecksDisplayFrame::getActiveInstance() { return instance; }

DecksDisplayFrame::DecksDisplayFrame(const int p_margin) : m_margin(p_margin)
{
	instance = this;
}

DecksDisplayFrame::~DecksDisplayFrame()
{
	instance = nullptr;
}

void DecksDisplayFrame::start() 
{
	this->m_slots.resize(1);
	this->m_slotTexts.resize(1);
	m_slots[0] = kitten::K_GameObjectManager::getInstance()->createNewGameObject("deck_display-deck-frame.json");
	m_slotTexts[0] = kitten::K_GameObjectManager::getInstance()->createNewGameObject("deck_display-deck-textbox.json");
	m_arrows[0] = kitten::K_GameObjectManager::getInstance()->createNewGameObject("deck_display-left_button.json");
	m_arrows[1] = kitten::K_GameObjectManager::getInstance()->createNewGameObject("deck_display-right_button.json");
	const glm::vec2 &deckScale = m_slots[0]->getTransform().getScale2D(),
		&displayFrameScale = this->m_attachedObject->getTransform().getScale2D(),
		&arrowButtons = m_arrows[0]->getTransform().getScale2D();
	const glm::vec3 &displayFrameTrans = m_attachedObject->getTransform().getTranslation();

	int textY = m_slotTexts[0]->getComponent<puppy::TextBox>()->getBoxHeight(),
		fittableX = (int)(displayFrameScale.x / (deckScale.x + 2 * m_margin)), // Formula: Usable Space/ Needed Space.  X: available width / (deck width + margins) 
		fittableY = (int)((displayFrameScale.y - (arrowButtons.y + 2 * m_margin)) / (deckScale.y + 4 * m_margin + textY)); // Y: (available height - button height ) / (deck height + text height+ margins) 

	this->m_slots.resize(std::fmax(fittableX*fittableY, 1));
	this->m_slotTexts.resize(std::fmax(fittableX*fittableY, 1));
	m_slots[0]->getTransform().place2D(displayFrameTrans.x + m_margin, displayFrameTrans.y + displayFrameScale.y - m_margin - deckScale.y);
	m_slotTexts[0]->getTransform().place2D(displayFrameTrans.x + m_margin, displayFrameTrans.y + displayFrameScale.y - 3 * m_margin - deckScale.y);
	m_arrows[0]->getTransform().place2D(displayFrameTrans.x + m_margin, displayFrameTrans.y + m_margin);
	m_arrows[1]->getTransform().place2D(displayFrameTrans.x + displayFrameScale.x - m_margin - arrowButtons.x, displayFrameTrans.y + m_margin);
	for (int i = 1; i < m_slots.size(); ++i)
	{
		m_slots[i] = kitten::K_GameObjectManager::getInstance()->createNewGameObject("deck_display-deck-frame.json");
		m_slots[i]->getTransform().place2D(
			displayFrameTrans.x + (i%fittableX)*(deckScale.x + 2 * m_margin) + m_margin,
			displayFrameTrans.y + displayFrameScale.y - (i / fittableX)*(deckScale.y + 4 * m_margin + textY) - m_margin - deckScale.y
		);
		m_slotTexts[i] = kitten::K_GameObjectManager::getInstance()->createNewGameObject("deck_display-deck-textbox.json");
		m_slotTexts[i]->getTransform().place2D(
			displayFrameTrans.x + (i%fittableX)*(deckScale.x + 2 * m_margin) + m_margin,
			displayFrameTrans.y + displayFrameScale.y - (i / fittableX)*(deckScale.y + 4 * m_margin + textY) - 3* m_margin - deckScale.y
		);
	}

	updateDeckDisplay();

	if (!sm_survivorFlagged)
	{
		kitten::K_GameObject * survivor = kitten::K_GameObjectManager::getInstance()->createNewGameObject("newgame_survivor.json");
		kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(survivor);
		sm_survivorFlagged = true;
	}
}


void DecksDisplayFrame::offsetCurrentSet(const int p_offset)
{
	int deckCount = kibble::getDeckDataListCount();
	if ((m_currentSet + p_offset)*m_slots.size() >= deckCount ||
		m_currentSet + p_offset < 0)
		return;
	this->m_currentSet += p_offset;
	updateDeckDisplay();
}


void DecksDisplayFrame::updateDeckDisplay() 
{
	int deckCount = kibble::getDeckDataListCount();
	m_currentActive = fmin(deckCount - (m_currentSet*m_slots.size()), m_slots.size());

	for (int i = 0; i < m_currentActive; ++i)
	{
		DeckData* deck = kibble::getDeckDataFromId(i + m_currentSet * m_slots.size());
		m_slots[i]->setEnabled(true);
		m_slotTexts[i]->setEnabled(true);
		m_slotTexts[i]->getComponent<puppy::TextBox>()->setText(deck->name);
		// TODO this is where to add deck or commander visual to deck front once set up right
	}
	for (int i = m_currentActive; i < m_slots.size();++i)
	{
		m_slots[i]->setEnabled(false);
		m_slotTexts[i]->setEnabled(false);
	}

	if (m_currentSet == 0) m_arrows[0]->setEnabled(false);
	else m_arrows[0]->setEnabled(true);

	if (m_currentActive != m_slots.size() &&
		m_slots.size() * (m_currentSet+1) > deckCount ) 
		m_arrows[1]->setEnabled(false);
	else m_arrows[1]->setEnabled(true);
}


void DecksDisplayFrame::onDisabled()
{
	for (auto slot : m_slots)
	{
		slot->setEnabled(false);
	}
	for (auto textBox : m_slotTexts)
	{
		textBox->setEnabled(false);
	}
	for (auto arrow : m_arrows)
	{
		arrow->setEnabled(false);
	}
}

void DecksDisplayFrame::onEnabled()
{
	for (int index = 0; index < m_currentActive; ++index)
	{
		m_slots[index]->setEnabled(true);
		m_slotTexts[index]->setEnabled(true);
	}
	if (m_currentSet == 0) m_arrows[0]->setEnabled(false);
	else m_arrows[0]->setEnabled(true);

	if (m_currentActive != m_slots.size() &&
		m_slots.size() * (m_currentSet + 1) > kibble::getDeckDataListCount())
		m_arrows[1]->setEnabled(false);
	else m_arrows[1]->setEnabled(true);
}


const int& DecksDisplayFrame::getCurrentPickedDeckId() const {
	return m_currentPick;
}
void DecksDisplayFrame::pickDisplayedDeck(const kitten::K_GameObject* p_gameObject) {
	m_currentPick =	std::find(m_slots.begin(), m_slots.end(), p_gameObject) - m_slots.begin() + (m_currentSet*m_slots.size());
}