#include "InitiativeTrackerUI.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"
#include "userinterface/UIFrame.h"
#include "puppy/Text/TextBox.h"

unit::InitiativeTrackerUI::InitiativeTrackerUI()
{
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		kitten::K_GameObject* frameObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		kitten::K_GameObject* textObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject();

		kitten::K_Component* frame = kitten::K_ComponentManager::getInstance()->createComponent("Frame");
		frameObject->addComponent(frame);
		m_frameList.push_back(frameObject);

		//for display unit name under ui frame
		puppy::TextBox* textbox = static_cast<puppy::TextBox*>(kitten::K_ComponentManager::getInstance()->createComponent("TextBox"));
		textbox->setColor(1, 1, 1);
		textObject->addComponent(textbox);
		m_textList.push_back(textObject);
	}

	setPosition();
	resetScale();
}

unit::InitiativeTrackerUI::~InitiativeTrackerUI()
{
}

void unit::InitiativeTrackerUI::turnStart()
{
	resetPosition();

	//first unit is the current unit take turn.
	m_firstShownUnitIterator = InitiativeTracker::getInstance()->m_currentUnitIterator;
	m_lastShownUnitIterator = InitiativeTracker::getInstance()->m_currentUnitIterator;

	//set all frames
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		m_frameIndexList[i] = i;
		setNewFrame(i);
	}
}

void unit::InitiativeTrackerUI::next()
{
	//move all frames left
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		if (m_frameIndexList[i] == 0)//if this is the first frame
		{
			//move first iterator
			m_firstShownUnitIterator++;

			//move frame to last
			moveX(m_maxUnitToShow-1,i);
			m_frameIndexList[i] = m_maxUnitToShow - 1;
			setNewFrame(i);
		}
		else
		{
			//move left
			moveX(m_frameIndexList[i] - 1, i);
			m_frameIndexList[i] --;
		}
	}
}

void unit::InitiativeTrackerUI::remove(const kitten::K_GameObject * p_unit)
{
	//find which slot display this unit
	int slotIndex = isShown(p_unit);
	if (slotIndex >= 0)//it is displayed in IT
	{
		 //find which frames
		for (int i=0; i<m_maxUnitToShow; i++)
		{
			if (m_frameIndexList[i] == slotIndex)//frame[i] display the unit
			{
				//move it to last
				moveX(m_maxUnitToShow - 1, i);
				m_frameIndexList[i] = m_maxUnitToShow - 1;
				setNewFrame(i);
			}
			else if (m_frameIndexList[i] > slotIndex)//frames in right will move left
			{
				moveX(m_frameIndexList[i] - 1, i);
				m_frameIndexList[i] --;
			}
		}
	}
}

int unit::InitiativeTrackerUI::isShown(const kitten::K_GameObject * p_unit)
{
	for (auto it = m_firstShownUnitIterator; it != m_lastShownUnitIterator; it++)
	{
		if ((*it) == p_unit)
		{
			int i = it - m_firstShownUnitIterator;
			return i;
		}
	}
	return -1;
}

void unit::InitiativeTrackerUI::setPosition()
{
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		float x = m_leftX + m_gap * i;
		m_xList.push_back(x);

		//initialize frame index list
		m_frameIndexList.push_back(0);
	}
}

void unit::InitiativeTrackerUI::moveX(int p_xI, int p_fI)
{
	float x = m_xList[p_xI];
	m_frameList[p_fI]->getTransform().place2D(x, m_frameY);
	m_textList[p_fI]->getTransform().place2D(x, m_textY);
}

void unit::InitiativeTrackerUI::resetPosition()
{
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		moveX(i, i);
	}
}

void unit::InitiativeTrackerUI::resetScale()
{
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		m_frameList[i]->getTransform().scale2D(m_scaleX, m_scaleY);
	}
}

void unit::InitiativeTrackerUI::setUIFrame(std::vector<kitten::K_GameObject*>::iterator p_unitIt, int p_index)
{
	kitten::K_GameObject* unitGO = *p_unitIt;

	//get texture
	std::string texPath = unitGO->getComponent<UnitGraphic>()->getTexturePath();
	//get name
	std::string name = unitGO->getComponent<Unit>()->m_name;

	//set texture
	m_frameList[p_index]->getComponent<userinterface::UIFrame>()->setTexture(texPath.c_str());

	//set name (textbox)
	m_textList[p_index]->getComponent<puppy::TextBox>()->setText(name);
}

void unit::InitiativeTrackerUI::setNewFrame(int p_index)
{
	if (m_lastShownUnitIterator != InitiativeTracker::getInstance()->m_unitObjectList.end())
	{//still has units in list
		setUIFrame(m_lastShownUnitIterator, p_index);
		m_lastShownUnitIterator++;
	}
	else
	{//no more units 
		m_frameList[p_index]->getComponent<userinterface::UIFrame>()->setTexture(m_blankTexture.c_str());
		m_textList[p_index]->getComponent<puppy::TextBox>()->setText("None");
	}
}

