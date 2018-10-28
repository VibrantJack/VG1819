#include "K_Instance.h"
#include "K_Routine.h"

#include <thread>
#include <iostream>

namespace kitten
{
	K_Instance* K_Instance::sm_instance = nullptr;

	K_Instance::K_Instance() : m_inputManager(input::InputManager::getInstance()), m_cameraList(K_CameraList::getInstance()),
		m_componentManager(K_ComponentManager::getInstance()), m_gameObjectManager(K_GameObjectManager::getInstance()),
		m_time(K_Time::getInstance()), m_clickables(ActiveClickables::getInstance()), m_eventManager(EventManager::getInstance()),
		m_jobManagerThread(BIND_FUNC(K_Instance, jobManagement), std::make_tuple(false))
	{
		m_jobManagerThread.run();
	}

	K_Instance::~K_Instance()
	{
		m_jobManagerThread.stop();
	}

	void K_Instance::createInstance()
	{
		assert(sm_instance == nullptr);

		input::InputManager::createInstance();
		K_CameraList::createInstance();
		K_ComponentManager::createInstance();
		K_GameObjectManager::createInstance();
		K_Time::createInstance();
		ActiveClickables::createInstance();
		EventManager::createInstance();
		AudioEngineWrapper::createInstance();	

		sm_instance = new K_Instance();
	}

	void K_Instance::destroyInstance()
	{
		assert(sm_instance != nullptr);

		input::InputManager::destroyInstance();
		K_CameraList::destroyInstance();
		K_ComponentManager::destroyInstance();
		K_GameObjectManager::destroyInstance();
		K_Time::destroyInstance();
		ActiveClickables::destroyInstance();
		EventManager::destroyInstance();
		AudioEngineWrapper::destroyInstance();

		delete sm_instance;
	}

	void K_Instance::update()
	{
		sm_instance->privateUpdate();
	}

	void K_Instance::addThreadedJob(K_Job* p_toAdd)
	{
		sm_instance->privateAddJob(p_toAdd);
	}

	void K_Instance::privateAddJob(K_Job* p_toAdd)
	{
		m_jobsToStart.push_back(p_toAdd);
	}

	void K_Instance::deleteAllJobs()
	{
		sm_instance->m_shouldDeleteJobs = true;
	}

	void K_Instance::startJobs()
	{
		auto it = m_jobsToStart.begin();
		while (it != m_jobsToStart.end())
		{
			(*it)->run();
			m_startedJobs.insert(*it);
			it = m_jobsToStart.erase(it);
		}
	}

	void K_Instance::privateDeleteAllJobs()
	{
		auto it = m_jobsToStart.begin();
		while (it != m_jobsToStart.end())
		{
			delete *it;
			m_jobsToStart.erase(it);
			it = m_jobsToStart.begin();
		}

		auto startedIt = m_startedJobs.begin();
		while (startedIt != m_startedJobs.end())
		{
			delete *startedIt;
			m_startedJobs.erase(startedIt);
			startedIt = m_startedJobs.begin();
		}
	}

	void K_Instance::jobManagement(std::tuple<bool> p_isDeleting)
	{
		bool shouldDelete = std::get<0>(p_isDeleting);

		if (shouldDelete)
		{
			privateDeleteAllJobs();
		}
		else
		{
			startJobs();
		}
	}

	void K_Instance::threadTest(std::tuple<void*> p_to)
	{
		std::cout << "THREAD TEST" << std::endl;
		for (int i = 0; i < 1; ++i)
		{
			std::cout << "i : " << i << std::endl;
		}
	}

	void K_Instance::privateUpdate()
	{
		if (m_shouldDeleteJobs && !m_deletedJobsLastFrame)
		{
			m_jobManagerThread.setParameters(std::make_tuple(true));
			m_deletedJobsLastFrame = true;
			m_shouldDeleteJobs = false;
		}
		else if(m_deletedJobsLastFrame)
		{
			m_deletedJobsLastFrame = false;
			m_jobManagerThread.setParameters(std::make_tuple(false));
		}

		AudioEngineWrapper::update();
		m_time->updateTime();
		m_inputManager->update();
		m_eventManager->update();

		m_componentManager->updateComponents();
		m_gameObjectManager->deleteQueuedObjects();
	}
}