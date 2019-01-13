#include "DragNDrop.h"
#include "kitten/InputManager.h"

#define TIME_TO_GO_BACK_TO_ORIGIN 0.025

DragNDrop::DragNDrop(bool p_backToOrigin) : m_backToOrigin(p_backToOrigin)
{

}

DragNDrop::~DragNDrop()
{

}

void DragNDrop::onClick() 
{
	m_isDragging = !m_isDragging;
	if (!m_isDragging)
	{
		onDrop();
	}
}

void DragNDrop::update()
{
	if (m_isDragging)
	{
		m_attachedObject->getTransform().place2D(
			input::InputManager::getInstance()->getMouseXPos() - 5,
			input::InputManager::getInstance()->getMouseYOpenGLPos() - getTransform().getScale2D().y + 5
		);
	}
}

void DragNDrop::start()
{
	m_isDragging = false;
	ClickableUI::start();
	m_lerpController = m_attachedObject->getComponent<LerpController>();
}

void DragNDrop::onDrop() // Override to set your custom own behavior
{
	if (m_backToOrigin)
	{
		//getTransform().place2D(m_origin.x, m_origin.y);
		m_lerpController->positionLerp(m_origin, TIME_TO_GO_BACK_TO_ORIGIN);
	}
}