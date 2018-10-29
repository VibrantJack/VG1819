#pragma once
#include <functional>
#include <thread>
#include <tuple>

namespace kitten
{
	class K_Job
	{	
	public:
		virtual void run() = 0;
		virtual void stop() = 0;
		virtual void setPaused(bool p_paused) = 0;
		virtual bool isRunning() = 0;
		virtual bool isFinished() = 0;
	};
	
}