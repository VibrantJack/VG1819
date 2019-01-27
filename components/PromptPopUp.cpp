#include "PromptPopUp.h"
#include "kitten/K_GameObjectManager.h"
#include "puppy/Text/TextBox.h"

void PromptPopUp::setBehavior(Behavior * p_connectedBehavior)
{
	this->m_connectedBehavior = p_connectedBehavior;
	m_mainObject->setEnabled(true);
	m_textBox->getComponent<puppy::TextBox>()->setText(this->m_connectedBehavior->m_text);
}

void PromptPopUp::start()
{
	m_mainObject = kitten::K_GameObjectManager::getInstance()->createNewGameObject("prompt_popup.json");
	m_backgroundFrame = &m_mainObject->getTransform().getChildren()[0]->getAttachedGameObject();
	m_successFrame = &m_mainObject->getTransform().getChildren()[1]->getAttachedGameObject();
	m_declineFrame = &m_mainObject->getTransform().getChildren()[2]->getAttachedGameObject();
	m_textBox = &m_mainObject->getTransform().getChildren()[3]->getAttachedGameObject();

	for (auto child : m_mainObject->getTransform().getChildren())
	{
		child->setIgnoreParent(true);
	}
	
	m_mainObject->setEnabled(false);
}

PromptPopUp * instance = nullptr;
PromptPopUp * PromptPopUp::getActiveInstance()
{
	return instance;
}

PromptPopUp::PromptPopUp()
{
	instance = this;
}

PromptPopUp::~PromptPopUp()
{
	instance = nullptr;
}
