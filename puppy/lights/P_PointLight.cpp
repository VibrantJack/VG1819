#include "P_PointLight.h"
#include "P_LightList.h"

namespace puppy
{
	P_PointLight::P_PointLight()
	{
		
	}

	P_PointLight::~P_PointLight()
	{
		P_LightList::getInstance()->removePointLight(this);
	}

	void P_PointLight::setPosition(const glm::vec3& p_pos)
	{
		m_position = p_pos;
	}

	void P_PointLight::setPointColor(const glm::vec3& p_color)
	{
		m_PointColor = glm::vec4(p_color, 1);
	}

	void P_PointLight::setAttenuation(const glm::vec3& p_atten)
	{
		m_attenuation = p_atten;
	}

	void P_PointLight::setRange(const float& p_range)
	{
		m_range = p_range;
	}

	const glm::vec4& P_PointLight::getPointColor() const
	{
		return m_PointColor;
	}

	const glm::vec3& P_PointLight::getPosition() const
	{
		return m_position;
	}

	const glm::vec3& P_PointLight::getAttenuation() const
	{
		return m_attenuation;
	}

	const float& P_PointLight::getRange() const
	{
		return m_range;
	}

	void P_PointLight::addToLightList() const
	{
		P_LightList::getInstance()->addPointLight(this);
	}

	void P_PointLight::removeFromLightList() const
	{
		P_LightList::getInstance()->removePointLight(this);
	}
}