#include "ClickableCard.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_GameObject.h"
#include <iostream>

namespace userinterface
{
	ClickableCard::ClickableCard()
	{

	}

	ClickableCard::~ClickableCard()
	{

	}

	void ClickableCard::onHoverStart()
	{
		std::cout << "Card Hover Started: Generating context menu...\n";

		kitten::K_GameObject* contextObj = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		kitten::K_Component* contextComp = kitten::K_ComponentManager::getInstance()->createComponent("ContextMenu");
		UIElement* ctxElement = static_cast<UIElement*>(contextComp);
		contextObj->addComponent(contextComp);
		m_context = contextObj;
		glm::vec2 origin = m_attachedFrame->getMinPoint();
		ctxElement->getTransform().place2D(origin.x, origin.y);
	}

	void ClickableCard::onHoverEnd()
	{
		std::cout << " Card Hover Ended.\n";

		if (m_context != nullptr)
		{
			m_context->setEnabled(false);
			kitten::K_GameObjectManager::getInstance()->destroyGameObject(m_context);
		}
	}
}