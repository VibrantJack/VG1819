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
		kitten::K_GameObject* gameObject;

		AmbientEvent(const glm::vec3& p_place, kitten::K_GameObject* p_go)
			: place(p_place), gameObject(p_go) {}
	};

private:

	kitten::K_Time* m_kTime;

	const float m_maxTimeToEvent, const m_minTimeToEvent;

	AmbientEvent* m_nextEvent;
	float m_currentTime, m_timeToNextEvent;

	std::vector<AmbientEvent> m_ambientEvents;

	virtual void start() override;
	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	//Helper methods
	void onNextEventNeeded();
public:
	AmbientSystemController(const std::vector<AmbientEvent>& p_ambientEvents, float p_minTimeBetweenEvents, float p_maxTimeBetweenEvents);
	~AmbientSystemController();
};
