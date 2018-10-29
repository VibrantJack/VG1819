#include "K_JobManager.h"
namespace kitten
{
	K_JobManager* K_JobManager::sm_instance = nullptr;

	void K_JobManager::createInstance()
	{
		assert(sm_instance == nullptr);
		sm_instance = new K_JobManager();
	}

	void K_JobManager::destroyInstance()
	{
		assert(sm_instance != nullptr);
		delete sm_instance;
		sm_instance = nullptr;
	}

	K_JobManager* K_JobManager::getInstance()
	{
		return sm_instance;
	}

	K_JobManager::K_JobManager() : m_jobManagerThread(BIND_FUNC(K_JobManager, jobCycle), std::make_tuple(false))
	{
		m_jobManagerThread.run();
	}

	K_JobManager::~K_JobManager()
	{
		m_jobManagerThread.stop();
		privateDeleteAllJobs();
	}

	void K_JobManager::addThreadedJob(K_Job* p_toAdd)
	{
		sm_instance->privateAddJob(p_toAdd);
	}

	void K_JobManager::privateAddJob(K_Job* p_toAdd)
	{
		m_jobsToStart.push_back(p_toAdd);
	}

	void K_JobManager::deleteAllJobs()
	{
		sm_instance->m_shouldDeleteJobs = true;
	}

	void K_JobManager::privateDeleteAllJobs()
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

	//This is run on a seperate thread
	void K_JobManager::jobCycle(std::tuple<bool> p_isDeleting)
	{
		bool shouldDelete = std::get<0>(p_isDeleting);

		if (shouldDelete)
		{
			privateDeleteAllJobs();
		}
		else
		{
			//Start jobs
			auto it = m_jobsToStart.begin();
			while (it != m_jobsToStart.end())
			{
				(*it)->run();
				m_startedJobs.insert(*it);
				it = m_jobsToStart.erase(it);
			}

			//Cleanup finished jobs
			for (auto startedIt = m_startedJobs.begin(); startedIt != m_startedJobs.end();)
			{
				if ((*startedIt)->isFinished())
				{
					delete *startedIt;
					startedIt = m_startedJobs.erase(startedIt);
				}
				else
				{
					++startedIt;
				}
			}
		}
	}

	void K_JobManager::update()
	{
		if (m_shouldDeleteJobs)
		{
			m_jobManagerThread.setParameters(std::make_tuple(true));
			m_deletedJobsLastFrame = true;
			m_shouldDeleteJobs = false;
		}
		else if (m_deletedJobsLastFrame)
		{
			m_deletedJobsLastFrame = false;
			m_jobManagerThread.setParameters(std::make_tuple(false));
		}
	}
}