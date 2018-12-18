#include "MoveByMouseRightClickDrag.h"
#include "kitten\InputManager.h"
#include "kitten\Transform.h"
#include "kitten\K_Time.h"

MoveByMouseRightClickDrag::MoveByMouseRightClickDrag(float p_speed) : m_speed(p_speed)
{

}

MoveByMouseRightClickDrag::~MoveByMouseRightClickDrag()
{

}

bool MoveByMouseRightClickDrag::hasUpdate() const
{
	return true;
}

void MoveByMouseRightClickDrag::update()
{
	input::InputManager* inputMan = input::InputManager::getInstance();
	if (inputMan->mouseDown(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float xChange = inputMan->getMouseXChange();
		float yChange = inputMan->getMouseYChange();

		kitten::Transform& transform = getTransform();

		//Don't actually have to use delta time here, mouse change is independent of framerate
		transform.move(xChange*m_speed, 0, yChange*m_speed);
	}
}