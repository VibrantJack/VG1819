#include "P_DirectionalLight.h"
#include "P_LightList.h"

namespace puppy
{
	P_DirectionalLight::P_DirectionalLight()
	{
		P_LightList::getInstance()->addDirectionalLight(this);
	}

	P_DirectionalLight::~P_DirectionalLight()
	{
		P_LightList::getInstance()->removeDirectionalLight(this);
	}

	void P_DirectionalLight::setPosition(const glm::vec3& p_pos)
	{
		m_position = p_pos;
	}

	void P_DirectionalLight::setAmbientColor(const glm::vec3& p_color)
	{
		m_ambientColor = p_color;
	}

	void P_DirectionalLight::setDirectionalColor(const glm::vec3& p_color)
	{
		m_directionalColor = p_color;
	}

	const glm::vec3& P_DirectionalLight::getAmbientColor() const
	{
		return m_ambientColor;
	}

	const glm::vec3& P_DirectionalLight::getDirectionalColor() const
	{
		return m_directionalColor;
	}

	const glm::vec3& P_DirectionalLight::getPosition() const
	{
		return m_position;
	}
}