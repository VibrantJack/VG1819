#pragma once

#include "util\MathUtil.h"
#include "kitten\K_Component.h"
#include "kitten\K_Time.h"

#include <vector>

class LerpController : public kitten::K_Component
{
public:
	class PositionLerpFinishedCallback
	{
	public:
		virtual void onPositionLerpFinished() = 0;
	};

	class ScaleLerpFinishedCallback
	{
	public:
		virtual void onScaleLerpFinished() = 0;
	};

	class RotationLerpFinishedCallback
	{
	public:
		virtual void onRotationLerpFinished() = 0;
	};

private:
	bool m_isLerping;
	bool m_isPositionLerping, m_isScaleLerping, m_isRotationLerping;

	glm::vec3 m_lerpPosition, m_originalPosition;
	glm::vec3 m_lerpScale, m_originalScale;
	glm::quat m_lerpQuat, m_originalQuat;

	float m_posLerpTime, m_scaleLerpTime, m_rotLerpTime;
	float m_posTimeElapsed, m_scaleTimeElapsed, m_rotTimeElapsed;

	std::vector<PositionLerpFinishedCallback*> m_posCallbacks;
	std::vector<ScaleLerpFinishedCallback*> m_scaleCallbacks;
	std::vector<RotationLerpFinishedCallback*> m_rotationCallbacks;

	kitten::K_Time* m_time;

	virtual void start();

	virtual bool hasUpdate() const override { return true; }
	virtual void update() override;

	inline void onFinishedLerp()
	{
		if (!m_isPositionLerping && !m_isScaleLerping && !m_isRotationLerping)
		{
			m_isLerping = false;
			setEnabled(false);
		}
	}

	inline void onStartLerp()
	{
		m_isLerping = true;
		setEnabled(true);
	}

public:
	LerpController();
	~LerpController();

	void positionLerp(const glm::vec3& p_pos, const float& p_time);
	void scaleLerp(const glm::vec3& p_scale, const float& p_time);
	void rotationLerp(const glm::quat& p_rot, const float& p_time);

	void addPositionCallback(PositionLerpFinishedCallback* p_listener);
	void addScaleCallback(ScaleLerpFinishedCallback* p_listener);
	void addRotationCallback(RotationLerpFinishedCallback* p_listener);

	void removePositionCallback(PositionLerpFinishedCallback* p_listener);
	void removeScaleCallback(ScaleLerpFinishedCallback* p_listener);
	void removeRotationCallback(RotationLerpFinishedCallback* p_listener);

	void forceLerpToFinish();
	void cancelLerp();

	bool isLerping() { return m_isLerping; }
	bool isPosLerping() { return m_isPositionLerping; }
	bool isScaleLerping() { return m_isScaleLerping; }
	bool isRotationLerping() { return m_isRotationLerping; }
};