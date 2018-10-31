#pragma once
#include "K_Job.h"
#include <cassert>

namespace kitten
{
	class K_JobManager;

	template<typename ... Args>
	class K_Routine : public K_Job
	{
		friend class K_JobManager;
	private:
		bool m_isRunning = false, m_isPaused = false, m_isRecurring, m_isFinished = false;
		std::function<void(std::tuple<Args...>)> m_toCall;
		std::tuple<Args...> m_parameter;

		std::thread m_thread;

		K_Routine(std::function<void(std::tuple<Args...>)> p_func, std::tuple<Args...> p_parameters, bool p_recurring = false) :
			m_toCall(p_func), m_parameter(p_parameters), m_isRecurring(p_recurring)
		{

		}

		~K_Routine()
		{
			if (m_isRunning)
			{
				m_isPaused = false;
				m_isRunning = false;
			}

			if (m_thread.joinable())
			{
				m_thread.join();
			}
		};

		// cycle() is the actual method called on the thread
		void cycle()
		{
			if (m_isRecurring)
			{
				while (m_isRunning)
				{
					m_toCall(m_parameter);

					while (m_isPaused)
					{
						//do nothing
					}
				}
			}
			else
			{
				m_toCall(m_parameter);
			}

			m_isFinished = true;
			m_isPaused = false;
		}

	public:

		virtual void run() override
		{
			assert(!m_isRunning); // your job is already running!
			m_isRunning = true;
			m_thread = std::thread(&K_Routine::cycle, this);
		}

		virtual void setParameters(std::tuple<Args...> p_parameters)
		{
			m_parameter = p_parameters;
		}

		virtual void setPaused(bool p_isPaused) override
		{
			if (m_isRunning)
			{
				m_isPaused = p_isPaused;
			}
			
		}

		virtual void stop() override
		{
			assert(m_isRunning);
			m_isRunning = false;
			m_isPaused = false;
			m_thread.join();
		}

		virtual bool isRunning() override 
		{ 
			return (m_isRecurring?m_isRunning && !m_isPaused:m_isRunning); 
		};

		virtual bool isFinished() override { return m_isFinished; };
	};
}
