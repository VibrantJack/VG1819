#pragma once
#include "K_Job.h"
#include <cassert>

#define BIND_FUNC(className, funcName) std::bind(&className::funcName, this, std::placeholders::_1)

namespace kitten
{
	template<typename ... Args>
	class K_Routine : public K_Job
	{
	private:
		bool m_isRunning = false, m_isPaused = false;
		std::function<void(std::tuple<Args...>)> m_toCall;
		std::tuple<Args...> m_parameter;

		std::thread m_thread;

		void cycle()
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
	public:
		K_Routine(std::function<void(std::tuple<Args...>)> p_func, std::tuple<Args...> p_parameters) : m_toCall(p_func), m_parameter(p_parameters)
		{

		}

		~K_Routine() { if (m_isRunning) m_thread.join(); };

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
			m_isPaused = p_isPaused;
		}

		virtual void stop() override
		{
			assert(m_isRunning);
			m_isRunning = false;
			m_isPaused = false;
			m_thread.join();
		}

		virtual bool isRunning() override { return m_isRunning; };
	};
}
