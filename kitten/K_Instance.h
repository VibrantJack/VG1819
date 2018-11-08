#pragma once
#include "InputManager.h"
#include "K_CameraList.h"
#include "K_ComponentManager.h"
#include "K_GameObjectManager.h"
#include "event_system\EventManager.h"
#include "K_Time.h"
#include "mouse picking\ActiveClickables.h"
#include "audio\AudioEngineWrapper.h"
#include "K_JobManager.h"
#include "util\AsyncFileOperations.h"

namespace kitten
{
	class K_Instance
	{
	private:
		K_Instance();
		~K_Instance();
		static K_Instance* sm_instance;

		input::InputManager* m_inputManager;
		K_CameraList* m_cameraList;
		K_ComponentManager* m_componentManager;
		K_GameObjectManager* m_gameObjectManager;
		EventManager* m_eventManager;
		K_Time* m_time;
		ActiveClickables* m_clickables;
		K_JobManager* m_jobManager;

		void privateUpdate();
	public:
		static void createInstance();

		static void update();

		static void destroyInstance();
	};
}