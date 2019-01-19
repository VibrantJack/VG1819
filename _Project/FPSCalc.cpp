#include "FPSCalc.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_ComponentManager.h"
#include <iostream>
#include "kitten\InputManager.h"

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
	if (m_fps < m_minFps)
		m_minFps = m_fps;
	if (m_fps > m_maxFps)
		m_maxFps = m_fps;
	m_textBox->setText("FPS: " + std::to_string(m_fps) + " Min: " + std::to_string(m_minFps) + " Max: " + std::to_string(m_maxFps));

	if (input::InputManager::getInstance()->keyDown(GLFW_KEY_ENTER) && !input::InputManager::getInstance()->keyDownLast(GLFW_KEY_ENTER))
	{
		m_minFps = 1000;
		m_maxFps = 0;
	}
}