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
		virtual void onPositionLerpFinished(kitten::K_GameObject* p_obj) = 0;
	};

	class ScaleLerpFinishedCallback
	{
	public:
		virtual void onScaleLerpFinished(kitten::K_GameObject* p_obj) = 0;
	};

	class RotationLerpFinishedCallback
	{
	public:
		virtual void onRotationLerpFinished(kitten::K_GameObject* p_obj) = 0;
	};

	enum TransformBehavior {
		ResetToOrigin, 
		KeepInPlace,
		SetToTarget
	};

	enum TransformSource {
		Local,
		World
	};

private:
	bool m_isLerping;
	bool m_isPositionLerping, m_isScaleLerping, m_isRotationLerping;
	bool m_isArcLerping, m_isArcRotating;

	glm::vec3 m_lerpPosition, m_originalPosition;
	float m_yHeight, m_halfArcRotLerpTime;
	bool m_arcingUp;

	glm::vec3 m_lerpScale, m_originalScale;
	glm::quat m_lerpQuat, m_originalQuat, m_endArcQuat;

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

	void positionLerp(const glm::vec3& p_pos, const float& p_time, TransformSource p_behavior = TransformSource::World);
	void scaleLerp(const glm::vec3& p_scale, const float& p_time, TransformSource p_behavior = TransformSource::World);
	void rotationLerp(const glm::quat& p_rot, const float& p_time, TransformSource p_behavior = TransformSource::World);

	void arcLerp(const glm::vec3& p_endPos, const float& p_time, const float& p_yHeight);
	void arcRotate(const glm::quat& p_maxRot, const glm::quat& p_endQuat, const float& p_time);

	void removePositionCallback(PositionLerpFinishedCallback* p_listener);
	void removeScaleCallback(ScaleLerpFinishedCallback* p_listener);
	void removeRotationCallback(RotationLerpFinishedCallback* p_listener);

	void endLerp(TransformBehavior p_behavior, bool p_applyCallbacks); // Does not disable, incase you want to replace the lerp
	void finishLerp(TransformBehavior p_behavior, bool p_applyCallbacks);// Disables

	bool isLerping() const { return m_isLerping; }
	bool isPosLerping() const { return m_isPositionLerping; }
	bool isScaleLerping() const { return m_isScaleLerping; }
	bool isRotationLerping() const { return m_isRotationLerping; }


	void addPositionLerpFinishedCallback(PositionLerpFinishedCallback* p_toAdd);
	void addScaleLerpFinishedCallback(ScaleLerpFinishedCallback* p_toAdd);
	void addRotationLerpFinishedCallback(RotationLerpFinishedCallback* p_toAdd);
	
};