#include "K_PointLight.h"

namespace kitten
{
	K_PointLight::K_PointLight(const glm::vec3& p_ambientColor, const glm::vec3& p_PointColor, const glm::vec3& p_attenuation, const float& p_range, bool p_useTransformCallbacks) : m_usingCallbacks(p_useTransformCallbacks)
	{
		m_puppyLight.setAmbientColor(p_ambientColor);
		m_puppyLight.setPointColor(p_PointColor);
		m_puppyLight.setAttenuation(p_attenuation);
		m_puppyLight.setRange(p_range);
	}

	K_PointLight::~K_PointLight()
	{
		getTransform().removePositionListener(this);
	}

	void K_PointLight::start()
	{
		if (m_usingCallbacks)
		{
			getTransform().addPositionListener(this);
			setEnabled(false);
		}

		m_puppyLight.setPosition(getTransform().getTranslation());
		m_puppyLight.addToLightList();
	}

	void K_PointLight::onEnabled()
	{
		m_puppyLight.addToLightList();
	}

	void K_PointLight::onDisabled()
	{
		m_puppyLight.removeFromLightList();
	}

	void K_PointLight::onPosChanged(const glm::vec3& p_newPos)
	{
		m_puppyLight.setPosition(p_newPos);
	}

	void K_PointLight::setAmbientColor(const glm::vec3& p_color)
	{
		m_puppyLight.setAmbientColor(p_color);
	}

	const glm::vec4& K_PointLight::getAmbientColor() const
	{
		return m_puppyLight.getAmbientColor();
	}

	void K_PointLight::setPointColor(const glm::vec3& p_color)
	{
		m_puppyLight.setPointColor(p_color);
	}

	const glm::vec4& K_PointLight::getPointColor() const
	{
		return m_puppyLight.getPointColor();
	}

	void K_PointLight::setAttenuation(const glm::vec3& p_atten)
	{
		m_puppyLight.setAttenuation(p_atten);
	}

	const glm::vec3& K_PointLight::getAttenuation() const
	{
		return m_puppyLight.getAttenuation();
	}

	void K_PointLight::setRange(const float& p_range)
	{
		m_puppyLight.setRange(p_range);
	}

	const float& K_PointLight::getRange() const
	{
		return m_puppyLight.getRange();
	}

	void K_PointLight::update()
	{
		assert(!m_usingCallbacks);
		m_puppyLight.setPosition(getTransform().getTranslation());
	}
}