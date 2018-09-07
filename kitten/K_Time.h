#pragma once
#include <cassert>

namespace kitten
{
	class K_Time
	{
	private:
		static K_Time* sm_instance;
		K_Time();
		~K_Time();

		double m_startTime;
		double m_deltaTime;
		double m_elapsedTime;

	public:
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new K_Time(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static K_Time * getInstance() { return sm_instance; };

		const double& getDeltaTime() const { return m_deltaTime; }
		const double& getElapsedTime() const { return m_elapsedTime; }

		void updateTime();
	};
}