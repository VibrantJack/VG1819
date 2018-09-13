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

		float changeScalar = m_speed * kitten::K_Time::getInstance()->getDeltaTime();

		transform.move(xChange*changeScalar, yChange*changeScalar, 0);
	}
}