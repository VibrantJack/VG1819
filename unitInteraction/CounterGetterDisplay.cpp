#include "CounterGetterDisplay.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten/K_ComponentManager.h"
#include "CounterGetter.h"
CounterGetterDisplay::CounterGetterDisplay()
	:m_maxGO(nullptr), m_minGO(nullptr), m_counterGO(nullptr)
{
}

CounterGetterDisplay::~CounterGetterDisplay()
{
}

void CounterGetterDisplay::setGetter(CounterGetter * p_g)
{
	m_getter = p_g;
}

void CounterGetterDisplay::set(int p_min, int p_max, const std::string & p_counter)
{
	m_min = p_min;
	m_max = p_max;
	m_counter = p_counter;

	m_current = m_min;

	if (m_maxGO == nullptr)
	{
		m_maxGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		puppy::TextBox* textBox = static_cast<puppy::TextBox*>(kitten::K_ComponentManager::getInstance()->createComponent("TextBox"));
		textBox->setColor(1, 1, 1);
		m_maxGO->addComponent(textBox);

		m_maxGO->getTransform().setParent(&m_attachedObject->getTransform());
		m_maxGO->getTransform().setIgnoreParent(false);
		m_maxGO->getTransform().place2D(-200, 0);
	}

	if (m_minGO == nullptr)
	{
		m_minGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		puppy::TextBox* textBox = static_cast<puppy::TextBox*>(kitten::K_ComponentManager::getInstance()->createComponent("TextBox"));
		textBox->setColor(1, 1, 1);
		m_minGO->addComponent(textBox);

		m_minGO->getTransform().setParent(&m_attachedObject->getTransform());
		m_minGO->getTransform().setIgnoreParent(false);
		m_minGO->getTransform().place2D(120,0);
	}

	if (m_counterGO == nullptr)
	{
		m_counterGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		puppy::TextBox* textBox = static_cast<puppy::TextBox*>(kitten::K_ComponentManager::getInstance()->createComponent("TextBox"));
		textBox->setColor(1, 1, 1);
		m_counterGO->addComponent(textBox);

		m_counterGO->getTransform().setParent(&m_attachedObject->getTransform());
		m_counterGO->getTransform().setIgnoreParent(false);
		m_counterGO->getTransform().place2D(-75, 50);
	}

	m_maxGO->getComponent<puppy::TextBox>()->setText("Min: "+std::to_string(m_max));
	m_minGO->getComponent<puppy::TextBox>()->setText("Max: " + std::to_string(m_min));
	m_counterGO->getComponent<puppy::TextBox>()->setText("Counter:"+m_counter);
}

void CounterGetterDisplay::start()
{
	m_textBox = m_attachedObject->getComponent<puppy::TextBox>();

	assert(m_textBox != nullptr);
	m_textBox->setText(std::to_string(m_current));
}

bool CounterGetterDisplay::hasUpdate() const
{
	return true;
}

void CounterGetterDisplay::update()
{
	if (input::InputManager::getInstance()->keyDown(GLFW_KEY_LEFT) &&
		!input::InputManager::getInstance()->keyDownLast(GLFW_KEY_LEFT))
	{
		m_current--;
		if (m_current < m_min)
		{
			m_current = m_max;
		}
		m_textBox->setText(std::to_string(m_current));
	}
	else if (input::InputManager::getInstance()->keyDown(GLFW_KEY_RIGHT) &&
		!input::InputManager::getInstance()->keyDownLast(GLFW_KEY_RIGHT) )
	{
		m_current++;
		if (m_current > m_max)
		{
			m_current = m_min;
		}
		m_textBox->setText(std::to_string(m_current));
	}
	else if (input::InputManager::getInstance()->keyDown(GLFW_KEY_ENTER) &&
		!input::InputManager::getInstance()->keyDownLast(GLFW_KEY_ENTER))
	{
		m_getter->getPlayerChoice(m_current);
	}
	else if (input::InputManager::getInstance()->keyDown(GLFW_KEY_SPACE) &&
		!input::InputManager::getInstance()->keyDownLast(GLFW_KEY_SPACE))
	{
		m_getter->cancel();
	}

}
