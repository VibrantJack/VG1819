#pragma once

#include "kitten\K_Component.h"
#include "kitten\Transform.h"
#include "kitten\Camera.h"

class ZoomByMouseWheel : public kitten::K_Component
{
private:

	kitten::Camera* m_cam;
	float m_speed;
	int m_minFOV, m_maxFOV;

public:
	ZoomByMouseWheel(nlohmann::json& p_json);
	ZoomByMouseWheel(float p_speed = 1.0f, int p_minFOV = 1, int p_m_maxFOV = 70);
	virtual ~ZoomByMouseWheel();

	virtual bool hasUpdate() const;

	virtual void update() override;
};