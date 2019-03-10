#include <iostream>

#include "InputManager.h"
#include "mouse picking\ActiveClickables.h"
#include "mouse picking\MousePicker.h"
#include "mouse picking\Ray.h"
#include "K_CameraList.h"
#include "puppy\ShaderManager.h"
#include "puppy\VertexEnvironment.h"
#include "event_system\EventManager.h"

#include <iostream>

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

	InputManager::InputManager() : m_shouldResetMouse(false), m_inputPollMode(true), m_notifyStringFinished(false), m_inputStringChanged(false)
	{
		memset(m_keysDown, 0, sizeof(bool) * GLFW_KEY_LAST);
		memset(m_keysDownLast, 0, sizeof(bool) * GLFW_KEY_LAST);

		//Set mouse to middle
		int windowXSize, windowYSize;
		glfwGetWindowSize(&windowXSize, &windowYSize);
		glfwSetMousePos(windowXSize / 2, windowYSize / 2);

		m_lastMouseX = windowXSize / 2;
		m_lastMouseY = windowYSize / 2;
		glfwEnable(GLFW_KEY_REPEAT);
	}

	InputManager::~InputManager()
	{
		glfwSetKeyCallback(nullptr);
		glfwSetCharCallback(nullptr);
	}

	void InputManager::resetMouse(bool p_shouldReset)
	{
		m_shouldResetMouse = p_shouldReset;
	}

	void InputManager::addStringListener(StringListener* p_toAdd)
	{
		m_stringListeners.insert(p_toAdd);
	}

	void InputManager::removeStringListener(StringListener* p_toRemove)
	{
		m_stringListeners.erase(p_toRemove);
	}

	void InputManager::setPollMode(bool p_enabled)
	{
		if (!p_enabled && m_inputPollMode)
		{
			for (int i = 0; i < GLFW_KEY_LAST; ++i)
			{
				m_keysDownLast[i] = false;
				m_keysDown[i] = false;
			}

			glfwSetKeyCallback(keyCallback);
			glfwSetCharCallback(charCallback);
		}
		else if (p_enabled && !m_inputPollMode)
		{
			glfwSetKeyCallback(nullptr);
			glfwSetCharCallback(nullptr);
			m_inputString = "";
		}

		m_inputPollMode = p_enabled;
	}

	void GLFWCALL InputManager::keyCallback(int key, int action)
	{
		sm_inputManagerInstance->privateKeyCallback(key, action);
	}

	void GLFWCALL InputManager::charCallback(int key, int action)
	{
		sm_inputManagerInstance->privateCharCallback(key, action);
	}

	void InputManager::privateKeyCallback(int key, int action)
	{
		if (!m_inputPollMode)
		{
			if (action == GLFW_PRESS && key == GLFW_KEY_ENTER)
			{
				m_inputPollMode = true;
				m_notifyStringFinished = true;

				glfwSetKeyCallback(nullptr);
				glfwSetCharCallback(nullptr);
			}
			else if (action == GLFW_PRESS && key == GLFW_KEY_BACKSPACE)
			{
				m_inputString = m_inputString.substr(0, m_inputString.length() - 1);
				m_inputStringChanged = true;
			}
			else if (action == GLFW_PRESS && key == GLFW_KEY_ESC)
			{
				m_inputPollMode = true;
				m_inputString = "";

				glfwSetKeyCallback(nullptr);
				glfwSetCharCallback(nullptr);
			}
		}
	}

	void InputManager::privateCharCallback(int key, int action)
	{
		if (!m_inputPollMode)
		{
			if (action == GLFW_PRESS)
			{
				m_inputString += (char)key;
				m_inputStringChanged = true;
			}
		}
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

	int InputManager::getMouseXPos()
	{
		return m_lastMouseX;
	}

	int InputManager::getMouseYWindowPos()
	{
		return m_lastMouseY;
	}

	int InputManager::getMouseYOpenGLPos()
	{
		return m_mouseYOpenGL;
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

	int InputManager::getWindowHeight()
	{
		return m_windowY;
	}

	int InputManager::getWindowWidth()
	{
		return m_windowX;
	}

	void InputManager::update()
	{
		if (m_inputPollMode && !m_notifyStringFinished)
		{
			for (int i = 0; i < GLFW_KEY_LAST; ++i)
			{
				m_keysDownLast[i] = m_keysDown[i];
				m_keysDown[i] = (glfwGetKey(i) == GLFW_PRESS);
			}
		}
		else if(m_notifyStringFinished)
		{
			//Clear the glfw buffer
			for (int i = 0; i < GLFW_KEY_LAST; ++i)
			{
				glfwGetKey(i);
			}
		}

		if (m_notifyStringFinished)
		{
			auto end = m_stringListeners.cend();
			for (auto it = m_stringListeners.cbegin(); it != end; ++it)
			{
				(*it)->onStringFinished(m_inputString);
			}

			m_inputString = "";
			m_notifyStringFinished = false;

			for (int i = 0; i < GLFW_KEY_LAST; ++i)
			{
				m_keysDownLast[i] = false;
				m_keysDown[i] = false;
			}
		}
		else if(m_inputStringChanged)
		{
			auto end = m_stringListeners.cend();
			for (auto it = m_stringListeners.cbegin(); it != end; ++it)
			{
				(*it)->onStringChanged(m_inputString);
			}

			m_inputStringChanged = false;
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
		glfwGetWindowSize(&m_windowX, &m_windowY);

		if (m_shouldResetMouse)
		{
			m_mouseXChange = ((float)m_windowX / 2.0f) - mouseX;
			m_mouseYChange = ((float)m_windowY / 2.0f) - mouseY;
			

			m_lastMouseX = mouseX;
			m_lastMouseY = mouseY;
			//Reset the position so it can't go out of screen
			glfwSetMousePos(m_windowX / 2, m_windowY / 2);
		}
		else
		{
			m_mouseXChange = m_lastMouseX - mouseX;
			m_mouseYChange = m_lastMouseY - mouseY;

			m_lastMouseX = mouseX;
			m_lastMouseY = mouseY;
		}

		//austin
		//Call for nearest UI frame
		m_mouseYOpenGL = m_windowY - m_lastMouseY;
		kitten::ClickableFrame* hitFrame = MousePicker::getClosestHitFrame((float) m_lastMouseX, m_mouseYOpenGL);
		kitten::ClickableFrame* lastHoverFrame = kitten::ActiveClickables::getInstance()->m_lastUIHover;

		bool blocking3DRayCast;

		// Update last hit object
		if (hitFrame != nullptr)
		{
			m_lastMouseHitFrame = &hitFrame->getGameObject();
			blocking3DRayCast = hitFrame->blocksRaycast();
		}
		else
		{
			m_lastMouseHitFrame = nullptr;
			blocking3DRayCast = false;
		}
		
		if (hitFrame != nullptr && lastHoverFrame != nullptr)
		{
			if (hitFrame != lastHoverFrame)
			{
				lastHoverFrame->onHoverEnd();
				hitFrame->onHoverStart();
				kitten::ActiveClickables::getInstance()->m_lastUIHover = hitFrame;
			}
		}
		else
		{
			if (hitFrame != nullptr && lastHoverFrame == nullptr)
			{
				hitFrame->onHoverStart();
				kitten::ActiveClickables::getInstance()->m_lastUIHover = hitFrame;
			}
			else if (hitFrame == nullptr && lastHoverFrame != nullptr)
			{
				if (lastHoverFrame == NULL)
				{
					assert(false);
				}
				lastHoverFrame->onHoverEnd();
				kitten::ActiveClickables::getInstance()->m_lastUIHover = nullptr;
			}
		}

		//Are we clicking a frame?
		if (m_mouseDown[GLFW_MOUSE_BUTTON_LEFT] && !m_mouseDownLast[GLFW_MOUSE_BUTTON_LEFT] && hitFrame != nullptr)
		{
			hitFrame->onClick();

			//Trigger event
			kitten::Event* p_data = new kitten::Event(kitten::Event::EventType::Object_Clicked);
			p_data->putGameObj(OBJECT_CLICKED_OBJ_KEY, &hitFrame->getGameObject());
			kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Object_Clicked, p_data);
		}
		//end UI click detection
		
		//Create ray from mouse location
			//Based on the method outlined in: http://antongerdelan.net/opengl/raycasting.html
			//@TODO: split-up into other methods?
		kitten::Ray mouseRay;

		kitten::Camera* activeCam = kitten::K_CameraList::getInstance()->getSceneCamera();

		mouseRay.origin = activeCam->getTransform().getTranslation();

		//Put mouse position in clipspace
		float ndX = (2.0f * mouseX) / m_windowX - 1.0f;
		float ndY = 1.0f - (2.0f * mouseY) / m_windowY;

		glm::vec3 clip = glm::vec3(ndX, ndY, 1.0f);

		//Put mouse into worldspace - mat3 to not have translation!
		glm::vec3 worldRay = (glm::inverse((glm::mat3)activeCam->getViewProj()) * clip);

		mouseRay.direction = glm::normalize(worldRay);

		kitten::ClickableBox* hit = MousePicker::getClosestHit(mouseRay);
		kitten::ClickableBox* lastHover = kitten::ActiveClickables::getInstance()->m_lastHover;

		// Update last hit object
		if (hit != nullptr) m_lastMouseHitObject = &hit->getGameObject();
		else m_lastMouseHitObject = nullptr;


		if (!blocking3DRayCast)
		{
			if (hit != nullptr && lastHover != nullptr)
			{
				if (lastHover != hit)
				{
					lastHover->onHoverEnd();
					hit->onHoverStart();
					kitten::ActiveClickables::getInstance()->m_lastHover = hit;
				}
			}
			else
			{
				if (hit != nullptr && lastHover == nullptr)
				{
					hit->onHoverStart();
					kitten::ActiveClickables::getInstance()->m_lastHover = hit;
				}
				else if (hit == nullptr && lastHover != nullptr)
				{
					if (lastHover == NULL)
					{
						assert(false);
					}
					lastHover->onHoverEnd();
					kitten::ActiveClickables::getInstance()->m_lastHover = nullptr;
				}
			}
			//Are we clicking?
			if (m_mouseDown[GLFW_MOUSE_BUTTON_LEFT] && !m_mouseDownLast[GLFW_MOUSE_BUTTON_LEFT] && hit != nullptr)
			{
				hit->onClick();

				//Trigger event
				kitten::Event* p_data = new kitten::Event(kitten::Event::EventType::Object_Clicked);
				p_data->putGameObj(OBJECT_CLICKED_OBJ_KEY, &hit->getGameObject());
				kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Object_Clicked, p_data);
			}
		}

		//Rock
		//trigger right click event
		if (m_mouseDown[GLFW_MOUSE_BUTTON_RIGHT] && !m_mouseDownLast[GLFW_MOUSE_BUTTON_RIGHT])
		{
			kitten::EventManager::getInstance()->triggerEvent(kitten::Event::EventType::Right_Clicked, nullptr);
		}

	}

	kitten::K_GameObject* InputManager::getMouseLastHitObject()
	{
		return m_lastMouseHitObject;
	}

	kitten::K_GameObject* InputManager::getMouseLastHitFrame()
	{
		return m_lastMouseHitFrame;
	}
}