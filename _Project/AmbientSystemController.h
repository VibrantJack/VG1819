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

	float m_maxTimeToEvent, m_minTimeToEvent;

	AmbientEvent m_nextEvent;
	float m_currentTime, m_timeToNextEvent;
	
	virtual void start() override;
	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	//Helper methods
	void onNextEventNeeded();
public:
	AmbientSystemController(float p_minTimeBetweenEvents, float p_maxTimeBetweenEvents);
	~AmbientSystemController();
};
