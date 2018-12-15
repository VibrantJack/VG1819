#include "CustomCursor.h"

CustomCursor::CustomCursor(int p_x, int p_y)
{
	m_offset = std::make_pair(p_x, p_y);
}

CustomCursor::~CustomCursor()
{
}

void CustomCursor::start()
{
	glfwDisable(GLFW_MOUSE_CURSOR);
}

bool CustomCursor::hasUpdate() const
{
	return true;
}

void CustomCursor::update()
{
	int mouseX, mouseY;
	glfwGetMousePos(&mouseX, &mouseY);

	//I don't know why but y is inversed, so I have to flip it
	int windowX, windowY;
	glfwGetWindowSize(&windowX, &windowY);
	mouseY = windowY - mouseY;

	//out of screen
	if (mouseX > windowX || mouseX < 0)
	{
		mouseX = m_lastX;
	}

	if (mouseY > windowY || mouseY < 0)
	{
		mouseY = m_lastY;
	}

	m_attachedObject->getTransform().place2D(mouseX, mouseY);
	m_lastX = mouseX;
	m_lastY = mouseY;
	m_attachedObject->getTransform().move2D(m_offset.first, m_offset.second);
}
