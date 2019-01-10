#include "ui/CardUIO.h"
#include "kitten\K_GameObjectManager.h"
#include "unit\Unit.h"

#define CARD_WIDTH 108.0f
#define CARD_HEIGHT 170.0f

#define PORTRAIT_X 16.0f
#define PORTRAIT_Y 63.0f

namespace userinterface
{
	CardUIO::CardUIO(const char* p_pathToTex) : UIObject(p_pathToTex)
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
		m_unitNameTextBox = unitName->getComponent<puppy::TextBox>();
		m_unitNameTextBox->setFont(puppy::FontTable::getInstance()->getFont("../fonts/nsimsun_14pt.fnt"));
		m_unitNameTextBox->setBoxBounds(CARD_WIDTH, 14.0f);
		m_unitNameTextBox->setAlignment(puppy::TextBox::center);
		m_unitNameTextBox->setText("Archer");
		m_unitNameTextBox->getTransform().place(0.0f, 162.0f, 0.01f);
		unitName->getTransform().setIgnoreParent(false);
		unitName->getTransform().setParent(&m_attachedObject->getTransform());

		kitten::K_GameObject* unitPortrait = kitten::K_GameObjectManager::getInstance()->createNewGameObject("card_context_texture.json");
		m_unitPortrait = unitPortrait->getComponent<UIObject>();
		m_unitPortrait->setTexture("textures/cards/500x500/Archer.tga");
		unitPortrait->getTransform().scaleAbsolute(78.0f, 78.0f, 0.0f);
		unitPortrait->getTransform().place(PORTRAIT_X, PORTRAIT_Y, 0.01f);
		unitPortrait->getTransform().setIgnoreParent(false);
		unitPortrait->getTransform().setParent(&m_attachedObject->getTransform());
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

}