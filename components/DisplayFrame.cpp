#include "DisplayFrame.h"
#include "kitten/K_GameObjectManager.h"
#include <math.h>
#include "CustomDataComponent.h"

#define SIZE_X "sizex"
#define SIZE_Y "sizey"

void DisplayFrame::start()
{
	// Set up all base gameobjects
	m_objectsToDisplay.resize(1);
	m_objectsToDisplay[0] = kitten::K_GameObjectManager::getInstance()->createNewGameObject(m_displayObject); // Remember that the scale of the whole object will be reset to 1,1. It's scale will be used to see how huge each object will be like
	m_arrows[0] = kitten::K_GameObjectManager::getInstance()->createNewGameObject(m_arrowFileLeft);
	m_arrows[1] = kitten::K_GameObjectManager::getInstance()->createNewGameObject(m_arrowFileRight);
	m_highlight = kitten::K_GameObjectManager::getInstance()->createNewGameObject(m_highlightFile); 
	m_empty = kitten::K_GameObjectManager::getInstance()->createNewGameObject(m_emptyFile); // Make sure whatever image is pivoted in the center for proper placement

	// Set up variables 
	const glm::vec2 &displayFrameScale = this->m_attachedObject->getTransform().getScale2D(), // The scale of the frame itself to see how big it is
		&arrowButtons = m_arrows[0]->getTransform().getScale2D(), // get the scales of  the arrows, to check how big those are
		objectScale = glm::vec2(m_objectsToDisplay[0]->getComponent<CustomDataComponent>()->m_intMap[SIZE_X],
			m_objectsToDisplay[0]->getComponent<CustomDataComponent>()->m_intMap[SIZE_Y]
			);// make sure the object has a custom data component with SIZE X and SIZE Y
	const glm::vec3 &displayFrameTrans = m_attachedObject->getTransform().getTranslation();

	// Reset object scale
	//m_objectsToDisplay[0]->getTransform().scale2D(1, 1);

	// Calculate how many objects can fit into our frame
	int fittableX = (int)((displayFrameScale.x - (arrowButtons.x + 2 * m_marginX) * 2) / (objectScale.x + 2 * m_marginX)), // Formula: Usable Space/ Needed Space.  X: available width - arrow with margins / (object width + margins) 
		fittableY = (int)((displayFrameScale.y) / (objectScale.y + 2 * m_marginY)); // Y: (available height) / (object height + margins) 

	// resize object vector to hold maximum possible to display
	this->m_objectsToDisplay.resize(std::fmax(fittableX*fittableY, 1));
	m_objectsToDisplay[0]->getTransform().place2D(displayFrameTrans.x + m_marginX, displayFrameTrans.y + displayFrameScale.y - m_marginY - objectScale.y); // remember, based on bottom left pivot

	m_arrows[0]->getTransform().place2D(displayFrameTrans.x - m_marginX - arrowButtons.x, displayFrameTrans.y + displayFrameScale.y / 2);
	m_arrows[1]->getTransform().place2D(displayFrameTrans.x + displayFrameScale.x + m_marginX, displayFrameTrans.y + displayFrameScale.y / 2);

	for (int i = 1; i < m_objectsToDisplay.size(); ++i)
	{
		m_objectsToDisplay[i] = kitten::K_GameObjectManager::getInstance()->createNewGameObject(m_displayObject);
		m_objectsToDisplay[i]->getTransform().place2D(
			displayFrameTrans.x + (i%fittableX)*(objectScale.x + 2 * m_marginX) + m_marginX,
			displayFrameTrans.y + displayFrameScale.y - (i / fittableX)*(objectScale.y + 2 * m_marginY) - m_marginY - objectScale.y
		);
	}

	updateDisplay();
}


void DisplayFrame::offsetCurrentSet(const int p_offset)
{
	if ((m_currentSet + p_offset)*m_objectsToDisplay.size() >= getTargetAvailable() || // checks if its going over the max
		m_currentSet + p_offset < 0)												   // checks if its going underneath minimum
		return;
	this->m_currentSet += p_offset;
	updateDisplay();
}


void DisplayFrame::updateDisplay()
{
	m_currentActive = fmin(getTargetAvailable() - (m_currentSet*m_objectsToDisplay.size()), m_objectsToDisplay.size());

	for (int i = 0; i < m_currentActive; ++i)
	{
		m_objectsToDisplay[i]->setEnabled(true);
		updateIndividualDisplayObject(i + m_currentSet * m_objectsToDisplay.size());
	}
	for (int i = m_currentActive; i < m_objectsToDisplay.size();++i)
	{
		m_objectsToDisplay[i]->setEnabled(false);
	}

	if (m_currentSet == 0) m_arrows[0]->setEnabled(false);
	else m_arrows[0]->setEnabled(true);

	if (m_currentActive != m_objectsToDisplay.size() &&
		m_objectsToDisplay.size() * (m_currentSet + 1) > getTargetAvailable())
		m_arrows[1]->setEnabled(false);
	else m_arrows[1]->setEnabled(true);

	if (getTargetAvailable() == 0)
	{
		m_empty->setEnabled(true);
	}
	else
	{
		m_empty->setEnabled(false);
	}

	updateHighlight();
}

void DisplayFrame::updateHighlight()
{
	if (m_currentPick >= 0 && m_currentPick >= m_currentSet * m_objectsToDisplay.size() && m_currentPick < (m_currentSet + 1) * m_objectsToDisplay.size())
	{
		m_highlight->setEnabled(true);
		m_highlight->getTransform().place2D(
			m_objectsToDisplay[m_currentPick%m_objectsToDisplay.size()]->getTransform().getTranslation()[0] + m_highlightOffset,
			m_objectsToDisplay[m_currentPick%m_objectsToDisplay.size()]->getTransform().getTranslation()[1] + m_highlightOffset
		);
		m_highlight->getTransform().place(
			m_highlight->getTransform().getTranslation().x,
			m_highlight->getTransform().getTranslation().y,
			-0.1
		);
	}
	else
	{
		m_highlight->setEnabled(false);
	}
}


void DisplayFrame::onDisabled()
{
	for (auto slot : m_objectsToDisplay)
	{
		slot->setEnabled(false);
	}
	for (auto arrow : m_arrows)
	{
		arrow->setEnabled(false);
	}
}

void DisplayFrame::onEnabled()
{
	for (int index = 0; index < m_currentActive; ++index)
	{
		m_objectsToDisplay[index]->setEnabled(true);
	}
	if (m_currentSet == 0) m_arrows[0]->setEnabled(false);
	else m_arrows[0]->setEnabled(true);

	if (m_currentActive != m_objectsToDisplay.size() &&
		m_objectsToDisplay.size() * (m_currentSet + 1) > getTargetAvailable())
		m_arrows[1]->setEnabled(false);
	else m_arrows[1]->setEnabled(true);
}


const int& DisplayFrame::getCurrentPickedObject() const {
	return m_currentPick;
}

int DisplayFrame::pickDisplayedObject(const kitten::K_GameObject* p_gameObject) {
	m_currentPick = std::find(m_objectsToDisplay.begin(), m_objectsToDisplay.end(), p_gameObject) - m_objectsToDisplay.begin() + (m_currentSet*m_objectsToDisplay.size());
	updateHighlight();
	return m_currentPick;
}