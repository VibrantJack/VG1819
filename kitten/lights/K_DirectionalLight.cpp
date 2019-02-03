#include "K_DirectionalLight.h"

namespace kitten
{
	K_DirectionalLight::K_DirectionalLight(const glm::vec3& p_ambientColor, const glm::vec3& p_directionalColor, bool p_useTransformCallbacks) : m_usingCallbacks(p_useTransformCallbacks)
	{
		m_puppyLight.setAmbientColor(p_ambientColor);
		m_puppyLight.setDirectionalColor(p_directionalColor);
	}

	K_DirectionalLight::~K_DirectionalLight()
	{
		getTransform().removePositionListener(this);
	}

	void K_DirectionalLight::start()
	{
		if (m_usingCallbacks)
		{
			getTransform().addPositionListener(this);
			setEnabled(false);
		}

		m_puppyLight.setPosition(getTransform().getTranslation());
		m_puppyLight.addToLightList();
	}

	void K_DirectionalLight::onEnabled()
	{
		m_puppyLight.addToLightList();
	}

	void K_DirectionalLight::onDisabled()
	{
		m_puppyLight.removeFromLightList();
	}

	void K_DirectionalLight::onPosChanged(const glm::vec3& p_newPos)
	{
		m_puppyLight.setPosition(p_newPos);
	}

	void K_DirectionalLight::setAmbientColor(const glm::vec3& p_color)
	{
		m_puppyLight.setAmbientColor(p_color);
	}

	const glm::vec4& K_DirectionalLight::getAmbientColor() const
	{
		return m_puppyLight.getAmbientColor();
	}

	void K_DirectionalLight::setDirectionalColor(const glm::vec3& p_color)
	{
		m_puppyLight.setDirectionalColor(p_color);
	}

	const glm::vec4& K_DirectionalLight::getDirectionalColor() const
	{
		return m_puppyLight.getDirectionalColor();
	}

	void K_DirectionalLight::update()
	{
		assert(!m_usingCallbacks);
		m_puppyLight.setPosition(getTransform().getTranslation());
	}
}