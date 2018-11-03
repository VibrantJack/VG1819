#include "InitiativeTrackerUI.h"
#include "unit/InitiativeTracker/TrackerBlock.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"
#include "ui/UIFrame.h"
#include "puppy/Text/TextBox.h"

unit::InitiativeTrackerUI::InitiativeTrackerUI()
{
	m_initiativeObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject();

	kitten::K_ComponentManager* comMan = kitten::K_ComponentManager::getInstance();
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		//initialize blocks
		unit::TrackerBlock* b = static_cast<unit::TrackerBlock*>(comMan->createComponent("TrackerBlock"));
		b->setTrackerUI(this);
		m_blockList.push_back(b);
		//add to game object
		m_initiativeObject->addComponent(b);

		//initialize block list
		m_blockInSlot.push_back(0);
		m_unitIndex.push_back(-1);
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

	m_lastUnitIndex = unit::InitiativeTracker::getInstance()->m_currentUnitIndex;

	//set all frames
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		m_blockInSlot[i] = i;
		setNewFrame(i);
	}
}

void unit::InitiativeTrackerUI::next()
{
	//move all frames left
	int temp = m_blockInSlot[0];
	for (int i = 0; i < m_maxUnitToShow - 1; i++)
	{
		m_blockInSlot[i] = m_blockInSlot[i + 1];
	}
	m_blockInSlot[m_maxUnitToShow - 1] = temp;

	//move every block to that position
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		int blockIndex = m_blockInSlot[i];
		m_blockList[blockIndex]->move(i);
	}

	//set new frame to block at last slot
	setNewFrame(m_blockInSlot[m_maxUnitToShow - 1]);
}

void unit::InitiativeTrackerUI::change(int p_i)
{//p_i is the index of unit
	int blockIndex = isShown(p_i);
	if (blockIndex >= 0)
	{
		//find the slot
		int slotIndex = -1;
		for (int i = 0; i < m_maxUnitToShow; i++)
		{
			if (m_blockInSlot[i] == blockIndex)//block is at slot i
			{
				slotIndex = i;
				break;
			}
		}
		
		//set last unit index to new unit
		m_lastUnitIndex = p_i;
		//set new frame for this block and block in the right slot
		for (int i = slotIndex; i < m_maxUnitToShow; i++)
		{
			setNewFrame(m_blockInSlot[i]);
		}
	}
	else if (blockIndex == -1)//unit is at front
	{
		m_lastUnitIndex++;//move last index right
	}
	else if (blockIndex == -2)//unit is at back
	{
		m_lastUnitIndex--;
	}
}

int unit::InitiativeTrackerUI::isShown(int p_i)
{
	if (p_i < m_unitIndex[0])//unit is before the first unit shown
	{
		return -1;
	}
	else if (p_i > m_unitIndex[m_maxUnitToShow - 1])//unit is after the last unit shown
	{
		return -2;
	}
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		if (m_unitIndex[i] == p_i)
			return i;
	}
	return -3;
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
	if (m_lastUnitIndex < InitiativeTracker::getInstance()->m_unitObjectList.size())
	{//still has units in list
		kitten::K_GameObject* unitGO = InitiativeTracker::getInstance()->m_unitObjectList[m_lastUnitIndex];
		m_blockList[p_index]->set(unitGO);
		m_unitIndex[p_index] = m_lastUnitIndex;
		m_lastUnitIndex++;
	}
	else
	{//no more units 
		m_blockList[p_index]->clear();
		m_unitIndex[p_index] = -1;
	}
}

