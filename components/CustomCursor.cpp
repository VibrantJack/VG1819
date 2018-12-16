#include "CustomCursor.h"
#include "kitten/K_GameObjectManager.h"

CustomCursor::CustomCursor(int p_x, int p_y)
{
	m_offset = std::make_pair(p_x, p_y);
}

CustomCursor::~CustomCursor()
{
	glfwEnable(GLFW_MOUSE_CURSOR);
}

void CustomCursor::start()
{
	//disable original mouse
	glfwDisable(GLFW_MOUSE_CURSOR);

	//make game object survive
	kitten::K_GameObjectManager::getInstance()->flagGameObjectToSurvive(m_attachedObject);
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

void CustomCursor::onEnabled()
{
	glfwDisable(GLFW_MOUSE_CURSOR);
}

void CustomCursor::onDisabled()
{
	glfwEnable(GLFW_MOUSE_CURSOR);
}
