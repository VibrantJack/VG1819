#include "CustomCursor.h"
#include "kitten/K_GameObjectManager.h"

CustomCursor::CustomCursor(int p_x, int p_y) : m_inputMan(nullptr)
{
	m_offset = std::make_pair(p_x, p_y);
}

CustomCursor::~CustomCursor()
{
	if(m_isEnabled)
	{
		onDisabled();
	}
}

void CustomCursor::start()
{
	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);

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
	int mouseX = m_inputMan->getMouseXPos();
	int mouseY = m_inputMan->getMouseYOpenGLPos();

	int windowX = m_inputMan->getWindowWidth();
	int windowY = m_inputMan->getWindowHeight();

	//out of screen
	if (mouseX > windowX || mouseX < 0)
	{
		mouseX = m_lastX;
		//glfwSetMousePos(mouseX, windowY - mouseY);
	}

	if (mouseY > windowY || mouseY < 0)
	{
		mouseY = m_lastY;
		//glfwSetMousePos(mouseX, windowY - mouseY);
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
