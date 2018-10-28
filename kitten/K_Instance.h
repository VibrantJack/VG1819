#pragma once
#include "InputManager.h"
#include "K_CameraList.h"
#include "K_ComponentManager.h"
#include "K_GameObjectManager.h"
#include "event_system\EventManager.h"
#include "K_Time.h"
#include "mouse picking\ActiveClickables.h"
#include "audio\AudioEngineWrapper.h"
#include "K_Routine.h"


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

		K_Routine<bool> m_jobManagerThread;

		bool m_shouldDeleteJobs = false;
		bool m_deletedJobsLastFrame = false;

		std::list<K_Job*> m_jobsToStart;
		std::unordered_set<K_Job*> m_startedJobs;

		void privateUpdate();
		void privateAddJob(K_Job* p_job);

		void jobManagement(std::tuple<bool> p_deleting);
		void startJobs();
		void privateDeleteAllJobs();

		void threadTest(std::tuple<void*> p_to);

	public:
		static void createInstance();

		static void addThreadedJob(K_Job* p_job);
		static void deleteAllJobs();

		static void update();

		static void destroyInstance();
	};
}