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
		kitten::K_GameObjectManager::getInstance()->destroyGameObject(m_context);
		getTransform().removePositionListener(this);
	}

	void ClickableCard::onHoverStart()
	{
		std::cout << "Card Hover Started: Generating context menu...\n";

		const glm::vec2& cardScale = getTransform().getScale2D();
		const glm::vec3& cardPos = getTransform().getTranslation();
		m_context->getTransform().place(0.0f, 0.0f, 0.1f);
		m_context->getTransform().place2D(cardPos.x, cardPos.y - 20);

		m_context->setEnabled(true);
		getTransform().addPositionListener(this);
	}

	void ClickableCard::onHoverEnd()
	{
		std::cout << " Card Hover Ended.\n";

		m_context->setEnabled(false);
		getTransform().removePositionListener(this);
	}

	void ClickableCard::onPosChanged(const glm::vec3 & p_newPos)
	{
		const glm::vec2& cardScale = getTransform().getScale2D();
		m_context->getTransform().place(0.0f, 0.0f, 0.1f);
		const glm::vec3& cardPos = getTransform().getTranslation();
		m_context->getTransform().place2D(cardPos.x, cardPos.y - 20);
	}
}