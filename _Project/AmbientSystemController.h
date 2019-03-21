#pragma once

#include "kitten\K_Component.h"
#include "kitten\K_Time.h"

class AmbientSystemController : public kitten::K_Component
{
private:
	enum AmbientEvent
	{
		wind, frogs, crickets, sword_in_stone_shine, fae, COUNT = fae + 1
	};

	kitten::K_Time* m_kTime;

	const glm::vec2 m_minPoint, const m_maxPoint;

	const float m_maxTimeToEvent, const m_minTimeToEvent;

	AmbientEvent m_nextEvent;
	float m_currentTime, m_timeToNextEvent;

	virtual void start() override;
	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	//Helper methods
	void onNextEventNeeded();
	glm::vec3 getEventPos() const;

	void playGenericEvent(const std::string& p_name, int p_randomIndex = 0, int p_randomMax = 0) const;
public:
	AmbientSystemController(const glm::vec2& p_minPoint, const glm::vec2& p_maxPoint, float p_minTimeBetweenEvents, float p_maxTimeBetweenEvents);
	~AmbientSystemController();
};
