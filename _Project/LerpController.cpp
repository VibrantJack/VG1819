#include "LerpController.h"
#include <iostream>

LerpController::LerpController() : m_time(nullptr), m_posLerpTime(0.0f), m_scaleLerpTime(0.0f), m_rotLerpTime(0.0f), 
	m_isLerping(false), m_isPositionLerping(false), m_isScaleLerping(false), m_isRotationLerping(false), m_yHeight(0), m_isArcLerping(false),
	m_isArcRotating(false)
{

}

LerpController::~LerpController()
{

}

void LerpController::start()
{
	if (!m_isLerping)
	{
		setEnabled(false);
	}

	m_time = kitten::K_Time::getInstance();
	assert(m_time != nullptr);
}

void LerpController::positionLerp(const glm::vec3& p_pos, const float& p_time, TransformSource p_behavior)
{
	m_isPositionLerping = true;
	m_isArcLerping = false;
	onStartLerp();

	m_lerpPosition = p_pos;
	m_posLerpTime = p_time;
	m_posTimeElapsed = 0.0f;
	switch (p_behavior) {
	case TransformSource::Local:
		m_originalPosition = getTransform().getRelativeTranslation();
		break;
	case TransformSource::World:
		m_originalPosition = getTransform().getTranslation();
		break;
	}
}

void LerpController::arcLerp(const glm::vec3& p_endPos, const float& p_time, const float& p_yHeight)
{
	positionLerp(p_endPos, p_time, TransformSource::World);

	m_isArcLerping = true;

	m_yHeight = p_yHeight + p_endPos.y;
}

void LerpController::rotationLerp(const glm::quat& p_rot, const float& p_time, TransformSource p_behavior)
{
	m_isRotationLerping = true;
	m_isArcRotating = false;
	onStartLerp();

	m_lerpQuat = p_rot;
	m_rotLerpTime = p_time;
	m_rotTimeElapsed = 0.0f;
	m_originalQuat = getTransform().getRotation();
}

void LerpController::arcRotate(const glm::quat& p_maxRot, const glm::quat& p_endQuat, const float& p_time)
{
	rotationLerp(p_maxRot, p_time, TransformSource::World);

	m_isArcRotating = true;
	m_arcingUp = true;

	m_endArcQuat = p_endQuat;
}

void LerpController::scaleLerp(const glm::vec3& p_scale, const float& p_time, TransformSource p_behavior)
{
	m_isScaleLerping = true;
	onStartLerp();

	m_lerpScale = p_scale;
	m_scaleLerpTime = p_time;
	m_scaleTimeElapsed = 0.0f;
	m_originalScale = getTransform().getLocalScale();
}

void LerpController::update()
{
	// Always lerping if we are in update
	// If the attached GO has been enabled, but we are not lerping, then disable ourselves
	if (!m_isLerping)
	{
		setEnabled(false);
		return;
	}

	float deltaTime = m_time->getDeltaTime();
	auto& transform = getTransform();

	if (m_isPositionLerping)
	{
		m_posTimeElapsed += deltaTime;
		float lerpProgress = m_posTimeElapsed / m_posLerpTime;
		
		if (lerpProgress >= 1.0f)
		{
			m_isPositionLerping = false;
			m_isArcLerping = false;

			transform.place(m_lerpPosition.x, m_lerpPosition.y, m_lerpPosition.z);

			onFinishedLerp();

			auto end = m_posCallbacks.cend();
			for (auto it = m_posCallbacks.cbegin(); it != end; ++it)
			{
				(*it)->onPositionLerpFinished();
			}
			m_posCallbacks.clear();
		}
		else
		{
			glm::vec3 newPos = LERP(lerpProgress, m_originalPosition, m_lerpPosition);
			
			if (m_isArcLerping)
			{
						   // y = -4x*(x-1)
				float curvedVal = -4 * (lerpProgress) * (lerpProgress - 1);

				float yOffset = LERP(curvedVal, m_originalPosition.y, m_yHeight);

				transform.place(newPos.x, newPos.y + yOffset, newPos.z);
			}
			else
			{
				transform.place(newPos.x, newPos.y, newPos.z);
			}
		}
	}

	if (m_isScaleLerping)
	{
		m_scaleTimeElapsed += deltaTime;
		float lerpProgress = m_scaleTimeElapsed / m_scaleLerpTime;

		if (lerpProgress >= 1.0f)
		{
			m_isScaleLerping = false;
			transform.scaleAbsolute(m_lerpScale.x, m_lerpScale.y, m_lerpScale.z);

			onFinishedLerp();

			auto end = m_scaleCallbacks.cend();
			for (auto it = m_scaleCallbacks.cbegin(); it != end; ++it)
			{
				(*it)->onScaleLerpFinished();
			}
			m_scaleCallbacks.clear();
		}
		else
		{
			glm::vec3 newScale = LERP(lerpProgress, m_originalScale, m_lerpScale);
			transform.scaleAbsolute(newScale.x, newScale.y, newScale.z);
		}
	}

	if (m_isRotationLerping)
	{
		m_rotTimeElapsed += deltaTime;
		float lerpProgress = m_rotTimeElapsed / m_rotLerpTime;

		if (lerpProgress >= 1.0f)
		{
			m_isRotationLerping = false;
			m_isArcRotating = false;
			transform.rotateAbsQuat(m_lerpQuat);

			onFinishedLerp();

			auto end = m_rotationCallbacks.cend();
			for (auto it = m_rotationCallbacks.cbegin(); it != end; ++it)
			{
				(*it)->onRotationLerpFinished();
			}
			m_rotationCallbacks.clear();
		}
		else
		{
			glm::quat newQuat;

			if (m_isArcRotating)
			{
				if (lerpProgress >= 0.5f)
				{
					m_arcingUp = false;
				}

				// y = -5x*(x-1)
				
				if (m_arcingUp)
				{
					float curvedVal = -4 * (lerpProgress) * (lerpProgress - 1);
					newQuat = LERP(curvedVal, m_originalQuat, m_lerpQuat);
				}
				else
				{
					float curvedVal = -4 * (lerpProgress-0.5f) * (lerpProgress - 0.5f - 1.0f);
					newQuat = LERP((curvedVal), m_lerpQuat, m_endArcQuat);
				}
			}
			else
			{
				newQuat = LERP(lerpProgress, m_originalQuat, m_lerpQuat);
			}

			transform.rotateAbsQuat(newQuat);
		}
	}
}

void LerpController::removePositionCallback(PositionLerpFinishedCallback* p_listener)
{
	m_posCallbacks.erase(std::find(m_posCallbacks.begin(),m_posCallbacks.end(), p_listener));
}

void LerpController::removeScaleCallback(ScaleLerpFinishedCallback* p_listener)
{
	m_scaleCallbacks.erase(std::find(m_scaleCallbacks.begin(), m_scaleCallbacks.end(), p_listener));
}

void LerpController::removeRotationCallback(RotationLerpFinishedCallback* p_listener)
{
	m_rotationCallbacks.erase(std::find(m_rotationCallbacks.begin(), m_rotationCallbacks.end(), p_listener));
}

void LerpController::endLerp(TransformBehavior p_behavior, bool p_applyCallbacks)
{
	if (!m_isLerping) return;
	if (m_isPositionLerping)
	{
		m_isPositionLerping = false;
		switch (p_behavior)
		{
		case TransformBehavior::ResetToOrigin:
			getTransform().place(m_originalPosition.x, m_originalPosition.y, m_originalPosition.z);
			break;
		case TransformBehavior::SetToTarget:
			getTransform().place(m_lerpPosition.x, m_lerpPosition.y, m_lerpPosition.z);
			break;
		}

		if (p_applyCallbacks)
		{
			auto end = m_posCallbacks.cend();
			for (auto it = m_posCallbacks.cbegin(); it != end; ++it)
			{
				(*it)->onPositionLerpFinished();
			}
			m_posCallbacks.clear();
		}
	}
	if (m_isScaleLerping)
	{
		m_isScaleLerping = false;

		switch (p_behavior)
		{
		case TransformBehavior::ResetToOrigin:
			getTransform().scaleAbsolute(m_originalScale.x, m_originalScale.y, m_originalScale.z);
			break;
		case TransformBehavior::SetToTarget:
			getTransform().scaleAbsolute(m_lerpScale.x, m_lerpScale.y, m_lerpScale.z);
			break;
		}

		if (p_applyCallbacks)
		{
			auto end = m_scaleCallbacks.cend();
			for (auto it = m_scaleCallbacks.cbegin(); it != end; ++it)
			{
				(*it)->onScaleLerpFinished();
			}
			m_scaleCallbacks.clear();
		}
	}
	if (m_isRotationLerping)
	{
		m_isRotationLerping = false;

		switch (p_behavior)
		{
		case TransformBehavior::ResetToOrigin:
			getTransform().rotateAbsQuat(m_originalQuat);
			break;
		case TransformBehavior::SetToTarget:
			getTransform().rotateAbsQuat(m_lerpQuat);
			break;
		}

		if (p_applyCallbacks)
		{
			auto end = m_rotationCallbacks.cend();
			for (auto it = m_rotationCallbacks.cbegin(); it != end; ++it)
			{
				(*it)->onRotationLerpFinished();
			}
			m_rotationCallbacks.clear();
		}
	}
}

void LerpController::finishLerp(TransformBehavior p_behavior, bool p_applyCallbacks)
{
	endLerp(p_behavior, p_applyCallbacks);
	onFinishedLerp();
}

void LerpController::addPositionLerpFinishedCallback(PositionLerpFinishedCallback* p_toAdd)
{
	m_posCallbacks.push_back(p_toAdd);
}

void LerpController::addScaleLerpFinishedCallback(ScaleLerpFinishedCallback* p_toAdd)
{
	m_scaleCallbacks.push_back(p_toAdd);
}

void LerpController::addRotationLerpFinishedCallback(RotationLerpFinishedCallback* p_toAdd)
{
	m_rotationCallbacks.push_back(p_toAdd);
}