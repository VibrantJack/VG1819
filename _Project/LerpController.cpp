#include "LerpController.h"

LerpController::LerpController() : m_time(nullptr), m_posLerpTime(0.0f), m_scaleLerpTime(0.0f), m_rotLerpTime(0.0f), 
	m_isLerping(false), m_isPositionLerping(false), m_isScaleLerping(false), m_isRotationLerping(false)
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

void LerpController::positionLerp(const glm::vec3& p_pos, const float& p_time)
{
	m_isPositionLerping = true;
	onStartLerp();

	m_lerpPosition = p_pos;
	m_posLerpTime = p_time;
	m_posTimeElapsed = 0.0f;
	m_originalPosition = getTransform().getTranslation();
}

void LerpController::rotationLerp(const glm::quat& p_rot, const float& p_time)
{
	m_isRotationLerping = true;
	onStartLerp();

	m_lerpQuat = p_rot;
	m_rotLerpTime = p_time;
	m_rotTimeElapsed = 0.0f;
	m_originalQuat = getTransform().getRotation();
}

void LerpController::scaleLerp(const glm::vec3& p_scale, const float& p_time)
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
	assert(m_isLerping);

	float deltaTime = m_time->getDeltaTime();
	auto& transform = getTransform();

	if (m_isPositionLerping)
	{
		m_posTimeElapsed += deltaTime;
		float lerpProgress = m_posTimeElapsed / m_posLerpTime;
		
		if (lerpProgress >= 1.0f)
		{
			transform.place(m_lerpPosition.x, m_lerpPosition.y, m_lerpPosition.z);
			
			m_isPositionLerping = false;
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
			transform.place(newPos.x, newPos.y, newPos.z);
		}
	}

	if (m_isScaleLerping)
	{
		m_scaleTimeElapsed += deltaTime;
		float lerpProgress = m_scaleTimeElapsed / m_scaleLerpTime;

		if (lerpProgress >= 1.0f)
		{
			transform.scaleAbsolute(m_lerpScale.x, m_lerpScale.y, m_lerpScale.z);

			m_isScaleLerping = false;
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
			transform.rotateAbsQuat(m_lerpQuat);

			m_isRotationLerping = false;
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
			glm::quat newQuat = LERP(lerpProgress, m_originalQuat, m_lerpQuat);
			transform.rotateAbsQuat(newQuat);
		}
	}
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