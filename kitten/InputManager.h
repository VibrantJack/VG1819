#pragma once
#include "puppy\P_Common.h"

namespace input
{
	class InputManager
	{
	private:
		static InputManager* sm_inputManagerInstance;

		bool m_keysDown[GLFW_KEY_LAST];
		bool m_keysDownLast[GLFW_KEY_LAST];

		float m_mouseXChange, m_mouseYChange;
		float m_lastMouseX, m_lastMouseY;

		bool m_shouldResetMouse;

		InputManager();
		~InputManager();
	public:
		
		static void createInstance();
		static void destroyInstance();
		static InputManager* getInstance();

		void resetMouse(bool p_shouldReset);

		bool keyDown(int p_key);
		bool keyDownLast(int p_key);

		int getMouseXChange();
		int getMouseYChange();

		void update();
	};
}