#include "InitiativeTrackerUI.h"
#include "unit/InitiativeTracker/TrackerBlock.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten\InputManager.h"
#include "UI/UIFrame.h"
#include "puppy/Text/TextBox.h"
#include "kitten\K_GameObject.h"
#include "UI\Borders\BorderPiece.h"
#include "kibble\kibble.hpp"

unit::InitiativeTrackerUI::InitiativeTrackerUI()
	:m_lastUnitIndex(0),
	m_leftX(-0.5f),
	m_gap(0.15f)
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
		//m_unitIndex.push_back(-1);
	}

	//background frame for initiative tracker
	kitten::K_GameObject* backGround = kibble::getGameObjectDataParserInstance()->getGameObject("UI/backgrounds/initiative_background.txt");
	int winY = input::InputManager::getInstance()->getWindowHeight();
	backGround->getTransform().place(300, winY -8, -0.04);

	//build partial borders
    //top
	kitten::K_GameObject* topBorder = kibble::getGameObjectDataParserInstance()->getGameObject("ui/borders/gold_border_top.txt");
	userinterface::BorderPiece* topBorderComp = topBorder->getComponent<userinterface::BorderPiece>();
	topBorderComp->setFramedObject(backGround);
	//topeleft
	kitten::K_GameObject* topleftBorder = kibble::getGameObjectDataParserInstance()->getGameObject("ui/borders/gold_border_topleft.txt");
	userinterface::BorderPiece* topleftBorderComp = topleftBorder->getComponent<userinterface::BorderPiece>();
	topleftBorderComp->setFramedObject(backGround);
	//topright
	kitten::K_GameObject* toprightBorder = kibble::getGameObjectDataParserInstance()->getGameObject("ui/borders/gold_border_topright.txt");
	userinterface::BorderPiece* toprightBorderComp = toprightBorder->getComponent<userinterface::BorderPiece>();
	toprightBorderComp->setFramedObject(backGround);
	//left
	kitten::K_GameObject* leftBorder = kibble::getGameObjectDataParserInstance()->getGameObject("ui/borders/gold_border_left.txt");
	userinterface::BorderPiece* leftBorderComp = leftBorder->getComponent<userinterface::BorderPiece>();
	leftBorderComp->setFramedObject(backGround);
	//right
	kitten::K_GameObject* rightBorder = kibble::getGameObjectDataParserInstance()->getGameObject("ui/borders/gold_border_right.txt");
	userinterface::BorderPiece* rightBorderComp = rightBorder->getComponent<userinterface::BorderPiece>();
	rightBorderComp->setFramedObject(backGround);

	//trackerframe
	setXList();

	//disabled - we don't need this anymore
	/*
	m_pointerObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
	kitten::K_Component* p = comMan->createComponent("TrackerPointer");
	m_pointerObject->addComponent(p);
	*/
}

unit::InitiativeTrackerUI::~InitiativeTrackerUI()
{
}

void unit::InitiativeTrackerUI::turnStart()
{
	resetPosition();

	int current = unit::InitiativeTracker::getInstance()->getCurrentUnitIndex();

	//set all frames
	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		m_blockInSlot[i] = i;
		setNewFrame(i, current+i );
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
	int current = unit::InitiativeTracker::getInstance()->getCurrentUnitIndex();
	setNewFrame(m_maxUnitToShow-1, m_lastUnitIndex+1);
}

void unit::InitiativeTrackerUI::change(int p_i)
{
	//p_i is the index of unit
	int blockIndex = isShown(p_i);
	if (blockIndex > 0)
	{
		//reset initiative tracker
		int current = InitiativeTracker::getInstance()->getCurrentUnitIndex();
		for (int i = 0; i < m_maxUnitToShow; i++)
		{
			setNewFrame(i, current + i);
		}
		
		/*
		int slot = p_i - current;
		//set this slot and all slot after it
		for (int i = slot; i < m_maxUnitToShow; i++)
		{
			setNewFrame(m_blockInSlot[i], current + i);
		}*/
	}
}

int unit::InitiativeTrackerUI::isShown(int p_i)
{
	int current = InitiativeTracker::getInstance()->getCurrentUnitIndex();
	if (p_i >= current && p_i < current + m_maxUnitToShow)
		return 1;//is shown
	else if (p_i < current)
		return 0;//before current unit
	else if (p_i >= current + m_maxUnitToShow)
		return -1;//after last unit possible

	/*
	if (p_i < m_unitIndex[m_blockInSlot[0]])//unit is before the first unit shown
	{
		return -1;
	}
	else if (p_i >= m_lastUnitIndex)//unit is after the last unit shown
	{
		for (int i = 0; i < m_maxUnitToShow; i++)
		{
			if (m_unitIndex[i] == -1)//return a block that is empty
				return i;
		}

		return -2;
	}

	for (int i = 0; i < m_maxUnitToShow; i++)
	{
		if (m_unitIndex[i] == p_i)
			return i;
	}*/

	assert(false);
	return -3;
}

void unit::InitiativeTrackerUI::setXList()
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

void unit::InitiativeTrackerUI::setNewFrame(int p_slot, int p_unit)
{//set slot p_slot to unit p_unit

	if (p_unit < InitiativeTracker::getInstance()->getUnitNumber())
	{//still has units in list
		kitten::K_GameObject* unitGO = InitiativeTracker::getInstance()->getUnitByIndex(p_unit);
		int block = m_blockInSlot[p_slot];
		m_blockList[block]->set(unitGO);

		m_lastUnitIndex = p_unit;
		/*
		m_unitShown++;
		if (m_unitShown > m_maxUnitToShow)
			m_unitShown = m_maxUnitToShow;*/
	}
	else
	{
		//no more units
		int block = m_blockInSlot[p_slot];
		m_blockList[block]->clear();
		/*
		m_unitShown--;
		if (m_unitShown < 0)
			m_unitShown = 0;*/
	}
	/*
	if (m_lastUnitIndex < InitiativeTracker::getInstance()->getUnitNumber())
	{//still has units in list
		kitten::K_GameObject* unitGO = InitiativeTracker::getInstance()->getUnitByIndex(m_lastUnitIndex);
		m_blockList[p_index]->set(unitGO);
		m_unitIndex[p_index] = m_lastUnitIndex;
		m_lastUnitIndex++;
	}
	else
	{//no more units 
		m_blockList[p_index]->clear();
		m_unitIndex[p_index] = -1;
	}*/
}

