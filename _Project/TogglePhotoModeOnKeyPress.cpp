#include "TogglePhotoModeOnKeyPress.h"

TogglePhotoModeOnKeyPress::TogglePhotoModeOnKeyPress(char p_key) : m_key(p_key), m_inputMan(nullptr)
{

}

TogglePhotoModeOnKeyPress::~TogglePhotoModeOnKeyPress()
{

}

void TogglePhotoModeOnKeyPress::start()
{
	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);

	m_boardMan = BoardManager::getInstance();
	assert(m_boardMan != nullptr);

	m_camera = m_attachedObject->getComponent<kitten::Camera>();
	assert(m_camera != nullptr);
}

void TogglePhotoModeOnKeyPress::update()
{
	if (m_inputMan->keyDown(m_key) && !m_inputMan->keyDownLast(m_key))
	{
		bool enabled = !(m_boardMan->isGridEnabled());
		
		m_boardMan->setGrid(enabled);
		m_camera->setRendersUI(enabled);
	}
}