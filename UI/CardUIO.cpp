#include "ui/CardUIO.h"
#include "kitten\K_GameObjectManager.h"
#include "unit\Unit.h"

#define CARD_WIDTH 108.0f
#define CARD_HEIGHT 170.0f

#define PORTRAIT_X 16.0f
#define PORTRAIT_Y 63.0f

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

		kitten::K_GameObject* unitName = kitten::K_GameObjectManager::getInstance()->createNewGameObject("card_context_textbox.json");
		unitName->getTransform().place(0.0f, 162.0f, 0.01f);
		unitName->getTransform().setIgnoreParent(false);
		unitName->getTransform().setParent(&m_attachedObject->getTransform());
		m_unitNameTextBox = unitName->getComponent<puppy::TextBox>();
		m_unitNameTextBox->setFont(puppy::FontTable::getInstance()->getFont("../fonts/nsimsun_14pt.fnt"));
		m_unitNameTextBox->setBoxBounds(CARD_WIDTH, 14.0f);
		m_unitNameTextBox->setAlignment(puppy::TextBox::center);

		kitten::K_GameObject* unitPortrait = kitten::K_GameObjectManager::getInstance()->createNewGameObject("card_context_texture.json");
		unitPortrait->getTransform().scaleAbsolute(78.0f, 78.0f, 0.0f);
		unitPortrait->getTransform().place(PORTRAIT_X, PORTRAIT_Y, 0.01f);
		unitPortrait->getTransform().setIgnoreParent(false);
		unitPortrait->getTransform().setParent(&m_attachedObject->getTransform());

		m_unitPortrait = unitPortrait->getComponent<UIObject>();
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