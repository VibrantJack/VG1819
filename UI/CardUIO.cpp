#include "ui/CardUIO.h"
#include "kitten\K_GameObjectManager.h"
#include "unit\Unit.h"

#define CARD_WIDTH 108.0f
#define CARD_HEIGHT 170.0f

#define PORTRAIT_X 78.0f
#define PORTRAIT_Y 78.0f

namespace userinterface
{
	CardUIO::CardUIO(const char* p_pathToTex) 
		: 
		UIObject(p_pathToTex), 
		m_unit(nullptr),
		m_unitPortrait(nullptr)
	{
		//nothing new to add
	}

	CardUIO::~CardUIO()
	{

	}

	void CardUIO::start()
	{
		UIElement::start();

		m_unitNameTextBox = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/hand_card/hand_card_textbox.json")->getComponent<puppy::TextBox>();
		m_unitNameTextBox->getTransform().setIgnoreParent(false);
		m_unitNameTextBox->getTransform().setParent(&m_attachedObject->getTransform());

		m_unitPortrait = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/hand_card/hand_card_texture.json")->getComponent<UIObject>();
		m_unitPortrait->getTransform().setIgnoreParent(false);
		m_unitPortrait->getTransform().setParent(&m_attachedObject->getTransform());
		m_unitPortrait->getTransform().scale2D(PORTRAIT_X / CARD_WIDTH, PORTRAIT_Y / CARD_HEIGHT);

		if (m_unit != nullptr)
		{
			m_unitPortrait->setTexture(m_unit->getPortraitTexturePath().c_str());
			m_unitNameTextBox->setText(m_unit->m_name);
		}
		else
		{
			m_unitPortrait->setTexture("textures/ui/blankFrame.tga");
			m_unitNameTextBox->setText("");
		}
	}

	void CardUIO::scaleAsCard()
	{
		getTransform().scale2D(CARD_WIDTH, CARD_HEIGHT);
	}


	void CardUIO::assignParentHand(HandFrame* p_toAssign)
	{
		m_parentHand = p_toAssign;
	}

	void CardUIO::returnToHand()
	{
		
	}

	void CardUIO::setUnit(unit::Unit* p_unit)
	{
		m_unit = p_unit;
		if (m_unitPortrait != nullptr)
		{
			m_unitPortrait->setTexture(m_unit->getPortraitTexturePath().c_str());
		}
	}
}