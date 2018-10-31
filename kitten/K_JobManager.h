#pragma once
#include "K_Job.h"
#include "K_Routine.h"
#include <list>
#include <unordered_set>

#define BIND_FUNC(className, funcName) std::bind(&className::funcName, this, std::placeholders::_1)

namespace kitten
{
	class K_Instance;

	class K_JobManager
	{
		friend class K_Instance;
	private:
		K_JobManager();
		~K_JobManager();
		static void createInstance();
		static void destroyInstance();
		static K_JobManager* sm_instance;

		K_Routine<bool> m_jobManagerThread;

		bool m_shouldDeleteJobs = false;
		bool m_deletedJobsLastFrame = false;

		std::list<K_Job*> m_jobsToStart;
		std::list<K_Job*> m_jobsToDelete;
		std::unordered_set<K_Job*> m_startedJobs;
		

		void update();
		void privateAddJob(K_Job* p_job);
		void privateDeleteJob(K_Job* p_job);

		void jobCycle(std::tuple<bool> p_deleting);
		void privateDeleteAllJobs();
	public:
		static K_JobManager* getInstance();

		template<typename ... Args>
		static K_Job* createJob(std::function<void(std::tuple<Args...>)> p_func, std::tuple<Args...> p_parameters, bool p_isRecurring = false)
		{
			K_Routine<Args...>* createdJob = new K_Routine<Args...>(p_func, p_parameters, p_isRecurring);
			sm_instance->privateAddJob(createdJob);
			return createdJob;
		}

		static void deleteJob(K_Job* p_job);

		static void addThreadedJob(K_Job* p_job);
		static void deleteAllJobs();
	};
}