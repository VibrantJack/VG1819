#include "FPSCalc.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_ComponentManager.h"
#include <iostream>

FPSCalc::FPSCalc()
{

}

FPSCalc::~FPSCalc()
{

}

void FPSCalc::start()
{
	m_timeRef = kitten::K_Time::getInstance();

	puppy::TextBox* text = m_attachedObject->getComponent<puppy::TextBox>();
	if (text == nullptr)
	{
		std::cerr << "FPSCalc could not find attached textbox and destroyed itself!" << std::endl;
		kitten::K_ComponentManager::getInstance()->destroyComponent(this);
		return;
	}

	m_textBox = text;
}

void FPSCalc::update()
{
	float deltaTime = m_timeRef->getDeltaTime();
	m_fps = 1.0f / m_timeRef->getDeltaTime();
	m_textBox->setText("FPS: " + std::to_string(m_fps));
}