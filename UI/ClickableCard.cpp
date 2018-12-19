#include "ClickableCard.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_GameObject.h"

#include "UIElement.h"
#include <iostream>

namespace userinterface
{
	ClickableCard::ClickableCard()
	{
		kitten::K_GameObject* contextObj = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		kitten::K_Component* contextComp = kitten::K_ComponentManager::getInstance()->createComponent("ContextMenu");
		contextObj->addComponent(contextComp);
		m_context = contextObj;
		
	}

	ClickableCard::~ClickableCard()
	{

	}

	void ClickableCard::onHoverStart()
	{
		std::cout << "Card Hover Started: Generating context menu...\n";

		glm::vec3 pos = getTransform().getTranslation();
		getTransform().place2D(pos.x, pos.y + 50);

		glm::vec2 cardScale = getTransform().getScale2D();
		glm::vec3 cardPos = getTransform().getTranslation();
		m_context->getTransform().place(0.0f, 0.0f, 0.1f);
		m_context->getTransform().place2D(cardPos.x, cardPos.y - 20);

		m_context->setEnabled(true);
	}

	void ClickableCard::onHoverEnd()
	{
		std::cout << " Card Hover Ended.\n";

		glm::vec3 pos = getTransform().getTranslation();
		getTransform().place2D(pos.x, pos.y - 50);

		m_context->setEnabled(false);
	}
}