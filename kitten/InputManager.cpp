#include <iostream>

#include "InputManager.h"
#include "mouse picking\ActiveClickables.h"
#include "mouse picking\MousePicker.h"
#include "mouse picking\Ray.h"
#include "K_CameraList.h"

namespace input
{
	// Static singleton instance
	InputManager* InputManager::sm_inputManagerInstance = nullptr;

	// Creates the singleton instance.
	void InputManager::createInstance()
	{
		assert(sm_inputManagerInstance == nullptr);
		sm_inputManagerInstance = new InputManager();
	}

	// Destroys the singleton instance.
	void InputManager::destroyInstance()
	{
		assert(sm_inputManagerInstance != nullptr);
		delete sm_inputManagerInstance;
		sm_inputManagerInstance = nullptr;
	}

	// Access to singleton instance.
	InputManager* InputManager::getInstance()
	{
		assert(sm_inputManagerInstance);
		return sm_inputManagerInstance;
	}

	InputManager::InputManager() : m_shouldResetMouse(true)
	{
		memset(m_keysDown, 0, sizeof(bool) * GLFW_KEY_LAST);
		memset(m_keysDownLast, 0, sizeof(bool) * GLFW_KEY_LAST);

		//Set mouse to middle
		int windowXSize, windowYSize;
		glfwGetWindowSize(&windowXSize, &windowYSize);
		glfwSetMousePos(windowXSize / 2, windowYSize / 2);

		m_lastMouseX = windowXSize / 2;
		m_lastMouseY = windowYSize / 2;
	}

	InputManager::~InputManager()
	{
		//delete arrays?
	}

	void InputManager::resetMouse(bool p_shouldReset)
	{
		m_shouldResetMouse = p_shouldReset;
	}

	bool InputManager::keyDown(int p_key)
	{
		return m_keysDown[p_key];
	}

	bool InputManager::keyDownLast(int p_key)
	{
		return m_keysDownLast[p_key];
	}

	bool InputManager::mouseDown(int p_button)
	{
		return m_mouseDown[p_button];
	}

	bool InputManager::mouseDownLast(int p_button)
	{
		return m_mouseDownLast[p_button];
	}

	int InputManager::getMouseXChange()
	{
		return m_mouseXChange;
	}

	int InputManager::getMouseYChange()
	{
		return m_mouseYChange;
	}

	int InputManager::getMouseWheel()
	{
		return m_mouseWheel;
	}

	void InputManager::update()
	{
		//Keys
		for (int i = 0; i < GLFW_KEY_LAST; ++i)
		{
			m_keysDownLast[i] = m_keysDown[i];
			m_keysDown[i] = (glfwGetKey(i) == GLFW_PRESS);
		}

		//Mouse
		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
		{
			m_mouseDownLast[i] = m_mouseDown[i];
			m_mouseDown[i] = (glfwGetMouseButton(i));
		}

		m_mouseWheel = glfwGetMouseWheel();
		glfwSetMouseWheel(0);

		int mouseX, mouseY;
		glfwGetMousePos(&mouseX, &mouseY);
		int windowX, windowY;
		glfwGetWindowSize(&windowX, &windowY);

		if (m_shouldResetMouse)
		{
			m_mouseXChange = ((float)windowX / 2.0f) - mouseX;
			m_mouseYChange = ((float)windowY / 2.0f) - mouseY;
			

			m_lastMouseX = mouseX;
			m_lastMouseY = mouseY;
			//Reset the position so it can't go out of screen
			glfwSetMousePos(windowX / 2, windowY / 2);
		}
		else
		{
			m_mouseXChange = m_lastMouseX - mouseX;
			m_mouseYChange = m_lastMouseY - mouseY;

			m_lastMouseX = mouseX;
			m_lastMouseY = mouseY;
		}

		
		
		//Create ray from mouse location
		//Based on the method outlined in: http://antongerdelan.net/opengl/raycasting.html
		//@TODO: split-up into other methods?
		kitten::Ray mouseRay;
		
		kitten::Camera* activeCam = kitten::K_CameraList::getInstance()->getSceneCamera();
		
		mouseRay.origin = activeCam->getTransform().getTranslation();

		//Put mouse position in clipspace
		float ndX = (2.0f * mouseX) / windowX - 1.0f;
		float ndY = 1.0f - (2.0f * mouseY) / windowY;
		glm::vec4 clip = glm::vec4(ndX, ndY, 1.0f, 1.0f);

		//Put mouse into worldspace
		glm::vec3 worldRay = (glm::vec3)(glm::inverse(activeCam->getViewProj()) * clip);

		/*
		glm::vec4 eye = glm::inverse(activeCam->getProj()) * clip;
		eye.z = -1.0f;
		eye.w = 0.0f;

		glm::vec3 worldRay = (glm::vec3)(activeCam->getMat4ViewInverse() * eye);
		*/

		mouseRay.direction = glm::normalize(worldRay);

		//Try to click on something
		if (m_mouseDown[GLFW_MOUSE_BUTTON_LEFT] && !m_mouseDownLast[GLFW_MOUSE_BUTTON_LEFT])
		{
			//@TODO: add support for hover start and hover end
			

			//try to click on the thing
			kitten::Clickable* hit = MousePicker::getClosestHit(mouseRay);

			if (hit != nullptr)
			{
				hit->onClick();
			}

		}
	}

}