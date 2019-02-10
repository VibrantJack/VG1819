#include "CounterGetter.h"
#include "kitten/K_ComponentManager.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten/QuadRenderable.h"
#include "UI/UIFrame.h"
#include "CounterGetterController.h"
CounterGetter::CounterGetter():m_displayWindowGO(nullptr)
{
	m_busy = false;
	registerEvent();
}

CounterGetter::~CounterGetter()
{
	//deregisterEvent();
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
		if (m_displayWindowGO == nullptr)
		{
			m_displayWindowGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject("counter_getter/counter_getter_display.json");
			m_displayWindowGO->getComponent<CounterGetterController>()->setGetter(this);

			/*
			m_displayWindowGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject();

			//textbox
			puppy::TextBox* textBox = static_cast<puppy::TextBox*>(kitten::K_ComponentManager::getInstance()->createComponent("TextBox"));
			textBox->setColor(1, 1, 1);
			textBox->setText("MAIN INTERACTIVE BOX");
			m_displayWindowGO->addComponent(textBox);

			//background texture
			userinterface::UIFrame* frame = static_cast<userinterface::UIFrame*>(kitten::K_ComponentManager::getInstance()->createComponent("Frame"));
			//kitten::QuadRenderable* q = static_cast<kitten::QuadRenderable*>(kitten::K_ComponentManager::getInstance()->createComponent("QuadRenderable"));
			//q->setTexture("texture/ui/line.tga");
			frame->setTexture("texture/ui/line.tga");
			m_displayWindowGO->addComponent(frame);

			//counter getter display
			m_displayWindowGO->addComponent(kitten::K_ComponentManager::getInstance()->createComponent("CounterGetterDisplay"));
			*/
			//m_displayWindowGO->getTransform().scale2D(10, 10);
			//m_displayWindowGO->getTransform().place2D(640.0f,360.0f);
		}
		
		m_displayWindowGO->setEnabled(true);
		m_displayWindowGO->getComponent<CounterGetterController>()->set(m_name, min, max);
		/*
		CounterGetterDisplay* display = m_displayWindowGO->getComponent<CounterGetterDisplay>();
		display->setGetter(this);
		display->set(min, max, m_name);*/

		m_busy = true;
	}
}

void CounterGetter::getPlayerChoice(int n)
{
	if (m_displayWindowGO != nullptr)
		m_displayWindowGO->setEnabled(false);

	m_busy = false;
	UnitInteractionManager::getInstance()->setCounter(m_name, n);
}

void CounterGetter::cancel()
{
	if (m_displayWindowGO != nullptr)
		m_displayWindowGO->setEnabled(false);

	m_busy = false;
	UnitInteractionManager::getInstance()->cancel();
}

void CounterGetter::registerEvent()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Right_Clicked,
		this,
		std::bind(&CounterGetter::listenEvent, this, std::placeholders::_1, std::placeholders::_2));

}

void CounterGetter::deregisterEvent()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::Right_Clicked, this);
}

void CounterGetter::listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	if (m_busy && p_type == kitten::Event::Right_Clicked)
	{
		cancel();
	}
}

void CounterGetter::reset()
{
	m_busy = false;
	m_displayWindowGO = nullptr;
}
