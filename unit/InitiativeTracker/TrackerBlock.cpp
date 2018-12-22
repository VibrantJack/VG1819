#pragma once
#include "TrackerBlock.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"
#include "puppy/Text/TextBox.h"
#include "UI/UIFrame.h"
#include "unit/InitiativeTracker/TrackerBlockClickable.h"

//static value
const std::string unit::TrackerBlock::sm_blankTexture = "textures/ui/blankFrame.tga";
const std::string unit::TrackerBlock::sm_blankText = "NONE";

const float unit::TrackerBlock::sm_scaleX = 96.0f;
const float unit::TrackerBlock::sm_scaleY = 108.0f;//scale for unit frame
const float unit::TrackerBlock::sm_frameY = 612.0f;//y coodinate for frame

const float unit::TrackerBlock::sm_halfWinX = 1280 / 2;
const float unit::TrackerBlock::sm_halfWinY = 720 / 2;
const float unit::TrackerBlock::sm_textY = 500.0f;

const float unit::TrackerBlock::sm_speed = 0.02f;

unit::TrackerBlock::TrackerBlock()
{
	//initialize
	kitten::K_GameObjectManager* goMan = kitten::K_GameObjectManager::getInstance();
	//frame object
	m_frameObject = goMan->createNewGameObject("tracker_block.json");
	//text object
	m_textObject = goMan->createNewGameObject("initiative_tracker_textbox.json");
	
	//component
	kitten::K_ComponentManager* comMan = kitten::K_ComponentManager::getInstance();
	
	/*
	//add frame
	kitten::K_Component* frame = comMan->createComponent("Frame");
	m_frameObject->addComponent(frame);
	kitten::K_Component* f = comMan->createComponent("ClickableFrame");
	m_frameObject->addComponent(f);
	kitten::K_Component* c = comMan->createComponent("TrackerBlockClickable");
	m_frameObject->addComponent(c);*/
	//add clickbox
	//kitten::K_Component* clickbox = comMan->createComponent("ClickableBoxForTrackerBlock");
	//m_frameObject->addComponent(clickbox);
	//add clickable
	//unit::TrackerBlockClickable* clickable = static_cast<unit::TrackerBlockClickable*>(comMan->createComponent("TrackerBlockClickable"));
	//m_frameObject->addComponent(clickable);

	//make text object be child of frame object
	m_textObject->getTransform().setParent(&m_frameObject->getTransform());
	m_textObject->getTransform().setIgnoreParent(false);

	//disable text object
	m_frameObject->getComponent<TrackerBlockClickable>()->setTextBox(m_textObject);

	//slot index
	m_currentSlotIndex = -1;
	m_targetSlotIndex = -1;
}

unit::TrackerBlock::~TrackerBlock()
{
	//TO DO
}

void unit::TrackerBlock::setTrackerUI(InitiativeTrackerUI * p_UI)
{
	m_trackerUI = p_UI;
}

void unit::TrackerBlock::start()
{
	//set scale
	m_frameObject->getTransform().scale2D(sm_scaleX, sm_scaleY);
}

void unit::TrackerBlock::move(int p_slotIndex)
{
	if (m_currentSlotIndex < 0)
	{
		//place block to the slot directly if it doesn't has slot yet
		m_currentSlotIndex = p_slotIndex;

		float x = m_trackerUI->m_xList[p_slotIndex];
		float xx = sm_halfWinX * (1.0f + x);

		m_frameObject->getTransform().place2D(xx, sm_frameY);
		//m_textObject->getTransform().place2D(xx, sm_textY);
	}
	else if (m_currentSlotIndex != (p_slotIndex + 1) )
	{
		//if current slot isn't at the target slot's right slot, place block there
		m_currentSlotIndex = p_slotIndex + 1;

		float x = m_trackerUI->m_xList[p_slotIndex + 1];
		float xx = sm_halfWinX * (1.0f + x);

		m_frameObject->getTransform().place2D(xx, sm_frameY);
		//m_textObject->getTransform().place2D(xx, sm_textY);
	}
	//then set target slot
	m_targetSlotIndex = p_slotIndex;
	//calc distance
	if (m_targetSlotIndex != m_currentSlotIndex)
	{
		float x1 = m_trackerUI->m_xList[m_targetSlotIndex];
		float x2 = m_trackerUI->m_xList[m_currentSlotIndex];
		distance = x1 - x2;
	}
}

void unit::TrackerBlock::set(kitten::K_GameObject* p_unitGO)
{
	//get texture
	std::string texPath = p_unitGO->getComponent<UnitGraphic>()->getTexturePath();
	//get name
	std::string name = p_unitGO->getComponent<Unit>()->m_name;

	//set texture
	m_frameObject->getComponent<userinterface::UIFrame>()->setTexture(texPath.c_str());

	//set name (textbox)
	m_textObject->getComponent<puppy::TextBox>()->setText(name);
}

void unit::TrackerBlock::clear()
{
	//set texture
	m_frameObject->getComponent<userinterface::UIFrame>()->setTexture(sm_blankTexture.c_str());

	//set name (textbox)
	m_textObject->getComponent<puppy::TextBox>()->setText(sm_blankText.c_str());
}

bool unit::TrackerBlock::hasUpdate() const
{
	return true;
}

void unit::TrackerBlock::update()
{
	//move when target slot is different from current slot
	if (m_targetSlotIndex != m_currentSlotIndex)
	{
		float velocity = kitten::K_Time::getInstance()->getDeltaTime() * sm_speed * 60.0f;//delta time * speed * 60fps

		if (distance == 0)//reaches target
			m_currentSlotIndex = m_targetSlotIndex;
		else
		{
			if (distance > 0)//move in positive direction
			{
				if (distance > velocity)//not close
				{
					//convert to text
					float xx = sm_halfWinX * velocity;
					m_frameObject->getTransform().move2D(xx, 0);
					//m_textObject->getTransform().move2D(xx,0);
					distance -= velocity;
				}
				else//vecy close, 
				{
					//convert to text
					float xx = sm_halfWinX * distance;
					m_frameObject->getTransform().move2D(xx, 0);
					//m_textObject->getTransform().move2D(xx, 0);
					distance = 0;
				}
			}
			else//negative direction
			{
				if (distance < -velocity)//not close
				{
					//convert to text
					float xx = sm_halfWinX * (-velocity);
					m_frameObject->getTransform().move2D(xx, 0);
					//m_textObject->getTransform().move2D(xx, 0);
					distance += velocity;
				}
				else//vecy close, 
				{
					//convert to text
					float xx = sm_halfWinX * distance;
					m_frameObject->getTransform().move2D(xx, 0);
					//m_textObject->getTransform().move2D(xx, 0);
					distance = 0;
				}
			}
		}
	}
}
