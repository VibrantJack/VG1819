#include "DragNDrop.h"
#include "kitten/InputManager.h"

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
		m_attachedObject->getTransform().move2D(
			-input::InputManager::getInstance()->getMouseXChange(),
			input::InputManager::getInstance()->getMouseYChange()
		);
	}
}

void DragNDrop::start()
{
	m_origin =	this->m_attachedObject->getTransform().getTranslation();
	m_isDragging = false;
	ClickableUI::start();
}

void DragNDrop::onDrop() // Override to set your custom own behavior
{
	if (m_backToOrigin)
	{
		getTransform().place2D(m_origin.x, m_origin.y);
	}
}