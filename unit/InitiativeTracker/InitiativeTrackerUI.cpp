#include "InitiativeTrackerUI.h"
#include "unit/InitiativeTracker/TrackerBlock.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"
#include "userinterface/UIFrame.h"
#include "puppy/Text/TextBox.h"

unit::InitiativeTrackerUI::InitiativeTrackerUI()
{
	kitten::K_ComponentManager* comMan = kitten::K_ComponentManager::getInstance();
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		//initialize blocks
		unit::TrackerBlock* b = static_cast<unit::TrackerBlock*>(comMan->createComponent("TrackerBlock"));
		b->setTrackerUI(this);
		m_blockList.push_back(b);

		//initialize frame index list
		m_frameIndexList.push_back(0);
	}
	setPosition();

	m_pointerObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
	kitten::K_Component* p = comMan->createComponent("TrackerPointer");
	m_pointerObject->addComponent(p);
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
			m_blockList[i]->move(m_maxUnitToShow - 1);
			m_frameIndexList[i] = m_maxUnitToShow - 1;
			setNewFrame(i);
		}
		else
		{
			//move left
			m_blockList[i]->move(--m_frameIndexList[i]);
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
				m_blockList[i]->move(m_maxUnitToShow - 1);
				m_frameIndexList[i] = m_maxUnitToShow - 1;
				setNewFrame(i);
			}
			else if (m_frameIndexList[i] > slotIndex)//frames in right will move left
			{
				m_blockList[i]->move(--m_frameIndexList[i]);
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
	//position list will have one more position
	for (int i = 0; i <= m_maxUnitToShow; i++)
	{
		float x = m_leftX + m_gap * i;
		m_xList.push_back(x);
	}
}

void unit::InitiativeTrackerUI::resetPosition()
{
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		m_blockList[i]->move(i);
	}
}

void unit::InitiativeTrackerUI::setNewFrame(int p_index)
{
	if (m_lastShownUnitIterator != InitiativeTracker::getInstance()->m_unitObjectList.end())
	{//still has units in list
		m_blockList[p_index]->set(m_lastShownUnitIterator);
		m_lastShownUnitIterator++;
	}
	else
	{//no more units 
		m_blockList[p_index]->clear();
	}
}

