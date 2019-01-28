#pragma once
#include "puppy\P_Common.h"

namespace puppy
{
	class P_PointLight
	{
	private:
		glm::vec3 m_position, m_attenuation;
		glm::vec4 m_PointColor, m_ambientColor;
		float m_range;

	public:
		P_PointLight();
		~P_PointLight();

		void setPosition(const glm::vec3& p_pos);
		void setPointColor(const glm::vec3& p_color);
		void setAmbientColor(const glm::vec3& p_color);
		void setAttenuation(const glm::vec3& p_attenuation); 
		void setRange(const float& p_range);

		const glm::vec3& getPosition() const;
		const glm::vec4& getPointColor() const;
		const glm::vec4& getAmbientColor() const;
		const glm::vec3& getAttenuation() const;
		const float& getRange() const;
	};
}
