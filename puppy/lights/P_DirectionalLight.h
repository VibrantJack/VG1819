#pragma once
#include "puppy\P_Common.h"

namespace puppy
{
	class P_DirectionalLight
	{
	private:
		glm::vec3 m_position;
		glm::vec4 m_directionalColor, m_ambientColor;

	public:
		P_DirectionalLight();
		~P_DirectionalLight();

		void setPosition(const glm::vec3& p_pos);
		void setDirectionalColor(const glm::vec3& p_color);
		void setAmbientColor(const glm::vec3& p_color);

		const glm::vec3& getPosition() const;
		const glm::vec4& getDirectionalColor() const;
		const glm::vec4& getAmbientColor() const;

		void addToLightList() const;
		void removeFromLightList() const;
	};
}
