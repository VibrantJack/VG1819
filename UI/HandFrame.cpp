#include "ui/HandFrame.h"
#include "glm/glm.hpp"
#include "kitten/K_GameObject.h"
#include "UIObject.h"
#include "kitten/Transform.h"
#include "ClickableCard.h"
#include "ContextMenu.h"

namespace userinterface
{
	HandFrame::HandFrame(const char* p_pathToTex) : UIFrame(p_pathToTex)
	{
		m_totalCards = 0;
		m_cardX = 100;
		m_cardY = 160;
		m_padding = 15;
		m_contentMargin = 10;
	}

	HandFrame::~HandFrame()
	{

	}

	void HandFrame::addCardToEnd(UIObject* p_cardToAdd)
	{
		m_innerObjects.push_back(p_cardToAdd);
		m_totalCards++;
		reorderAllCards();
	}

	//TODO: Assign parent frame when object is added
	void HandFrame::addCardToFront(UIObject* p_cardToAdd)
	{
		m_innerObjects.push_front(p_cardToAdd);
		m_totalCards++;
		reorderAllCards();
	}

	void HandFrame::removeCard(UIObject* p_cardToRemove)
	{
		auto end = m_innerObjects.end();
		for (auto it = m_innerObjects.begin(); it != end; ++it)
		{
			if (*it = p_cardToRemove)
			{
				m_innerObjects.erase(it);
			}
		}
		m_totalCards--;
		reorderAllCards();
	}

	void HandFrame::reorderAllCards()
	{
		kitten::Transform T = getTransform();
		glm::vec3 trans = T.getTranslation();
		float offset = m_padding;
		auto end = m_innerObjects.end();
		for (auto it = m_innerObjects.begin(); it != end; ++it)
		{
			(*it)->getTransform().place2D(trans.x + offset, trans.y + m_padding);
			offset += m_cardX;
			offset += m_contentMargin;
		}
	}

}


#include "kitten/K_GameObjectManager.h"
#include "kitten/K_ComponentManager.h"
#include "UI/CardUIO.h"
void userinterface::HandFrame::makeAHand() {
	kitten::K_GameObject* hand = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
	kitten::K_Component* handFrame = kitten::K_ComponentManager::getInstance()->createComponent("Hand");
	userinterface::HandFrame* frameCasted = static_cast<userinterface::HandFrame*>(handFrame);

	hand->addComponent(handFrame);
	hand->getTransform().scale2D(600.0f, 150.0f);
	hand->getTransform().place2D(30.0, -100.0);
	hand->setEnabled(false);

	for (int x = 0; x < 5; x++)
	{
		kitten::K_GameObject* card = kitten::K_GameObjectManager::getInstance()->createNewGameObject("handcard.json");
		userinterface::CardUIO* cardCasted = card->getComponent<userinterface::CardUIO>();
		cardCasted->scaleAsCard();

		frameCasted->addCardToEnd(cardCasted);
		cardCasted->assignParentHand(frameCasted);

		kitten::K_Component* clickableCom = kitten::K_ComponentManager::getInstance()->createComponent("ClickableCard");
		card->addComponent(clickableCom);
	}
}

