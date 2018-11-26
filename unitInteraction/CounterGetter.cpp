#include "CounterGetter.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten/QuadRenderable.h"
#include "UI/UIFrame.h"
CounterGetter::CounterGetter():m_displayWindoGO(nullptr)
{
}

CounterGetter::~CounterGetter()
{
}

void CounterGetter::requireCounter(unit::AbilityDescription * p_ad, unit::Unit * p_source)
{
	m_name = p_ad->m_stringValue[COUNTER_NAME];//get counter name

	//then get selection method
	std::string method = p_ad->m_stringValue[COUNTER_SELECT];

	if (method == COUNTER_ALL)//cost all counter
	{
		getAllCounter(p_source);
	}
	else if (method == COUNTER_CHOOSE)//player choose the cost
	{
		playerChooseCounter(p_ad, p_source);
	}
}

void CounterGetter::getAllCounter(unit::Unit * p_source)
{
	auto it2 = p_source->m_attributes.find(m_name);
	if (it2 != p_source->m_attributes.end())
	{
		int n = it2->second;
		UnitInteractionManager::getInstance()->setCounter(m_name, n);
	}
	else
	{//don't have counter
		UnitInteractionManager::getInstance()->setCounter(m_name, 0);
	}
}

void CounterGetter::playerChooseCounter(unit::AbilityDescription * p_ad, unit::Unit * p_source)
{
	int min = 0;
	int max = 0;
	auto it2 = p_source->m_attributes.find(m_name);
	if (it2 != p_source->m_attributes.end())
	{
		max = it2->second;//set max
	}

	auto it3 = p_ad->m_intValue.find(COUNTER_MAX);
	if (it3 != p_ad->m_intValue.end())
	{
		int n = it3->second;//max
		if (n < max)
			max = n;
	}
	auto it4 = p_ad->m_intValue.find(COUNTER_MIN);
	if (it4 != p_ad->m_intValue.end())
	{
		int n = it4->second;//min
		if (n > min)
			min = n;
	}

	if (max < min)
		UnitInteractionManager::getInstance()->cancel();
	else
	{
		if (m_displayWindoGO == nullptr)
		{
			m_displayWindoGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject();

			//textbox
			puppy::TextBox* textBox = static_cast<puppy::TextBox*>(kitten::K_ComponentManager::getInstance()->createComponent("TextBox"));
			textBox->setColor(1, 1, 1);
			textBox->setText("MAIN INTERACTIVE BOX");
			m_displayWindoGO->addComponent(textBox);

			//background texture
			userinterface::UIFrame* frame = static_cast<userinterface::UIFrame*>(kitten::K_ComponentManager::getInstance()->createComponent("Frame"));
			//kitten::QuadRenderable* q = static_cast<kitten::QuadRenderable*>(kitten::K_ComponentManager::getInstance()->createComponent("QuadRenderable"));
			//q->setTexture("texture/ui/line.tga");
			frame->setTexture("texture/ui/line.tga");
			m_displayWindoGO->addComponent(frame);

			//counter getter display
			m_displayWindoGO->addComponent(kitten::K_ComponentManager::getInstance()->createComponent("CounterGetterDisplay"));

			m_displayWindoGO->getTransform().place2D(640.0f,360.0f);
		}

		m_displayWindoGO->setEnabled(true);
		CounterGetterDisplay* display = m_displayWindoGO->getComponent<CounterGetterDisplay>();
		display->setGetter(this);
		display->set(min, max, m_name);
	}
}

void CounterGetter::getPlayerChoice(int n)
{
	m_displayWindoGO->setEnabled(false);

	UnitInteractionManager::getInstance()->setCounter(m_name, n);
}

void CounterGetter::cancel()
{
	m_displayWindoGO->setEnabled(false);

	UnitInteractionManager::getInstance()->cancel();
}
