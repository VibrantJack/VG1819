#pragma once

#include "kitten\K_Component.h"
#include "kitten\K_Time.h"

#include <vector>

class AmbientSystemController : public kitten::K_Component
{
public:
	struct AmbientEvent
	{
		const glm::vec3 place;
		const float minTimeBetweenEvents, const maxTimeBetweenEvents;
		float timeElapsed = 0.0f, timeToNextEvent = 0.0f;
		kitten::K_GameObject* gameObject;

		AmbientEvent(const glm::vec3& p_place, kitten::K_GameObject* p_go, float p_minTime, float p_maxtTime)
			: place(p_place), gameObject(p_go), minTimeBetweenEvents(p_minTime), maxTimeBetweenEvents(p_maxtTime) 
		{
			reset();
		}

		bool isReady() const { return timeElapsed >= timeToNextEvent; }
		void update(float p_deltaTime) { timeElapsed += p_deltaTime; }
		void reset()
		{
			timeElapsed = 0.0f;
			timeToNextEvent = LERP(((float)rand() / (float)RAND_MAX), minTimeBetweenEvents, maxTimeBetweenEvents);
		}
	};

private:

	kitten::K_Time* m_kTime;

	std::vector<AmbientEvent> m_ambientEvents;

	virtual void start() override;
	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;
public:
	AmbientSystemController(const std::vector<AmbientEvent>& p_ambientEvents);
	~AmbientSystemController();
};
