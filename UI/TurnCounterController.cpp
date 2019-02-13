#include "TurnCounterController.h"

TurnCounterController::TurnCounterController()
	:m_turnCounter(0),
	m_text(nullptr)
{
	registerEvent();
}

TurnCounterController::~TurnCounterController()
{
	deregisterEvent();
}

void TurnCounterController::start()
{
	m_text = m_attachedObject->getComponent<puppy::TextBox>();
	changeText();
}

void TurnCounterController::registerEvent()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::New_Game_Turn,
		this,
		std::bind(&TurnCounterController::listenEvent, this, std::placeholders::_1, std::placeholders::_2));

}

void TurnCounterController::deregisterEvent()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::New_Game_Turn, this);
}

void TurnCounterController::listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	if (p_type == kitten::Event::New_Game_Turn)
	{
		m_turnCounter++;
		changeText();
	}
}

void TurnCounterController::changeText()
{
	if(m_text != nullptr)
		m_text->setText("Turn:" + std::to_string(m_turnCounter));
}
