#pragma once
#include "puppy\P_Common.h"

namespace puppy
{
	class P_DirectionalLight
	{
	private:
		glm::vec3 m_position, m_directionalColor, m_ambientColor;
	public:
		P_DirectionalLight();
		~P_DirectionalLight();

		void setPosition(const glm::vec3& p_pos);
		void setDirectionalColor(const glm::vec3& p_color);
		void setAmbientColor(const glm::vec3& p_color);

		const glm::vec3& getPosition() const;
		const glm::vec3& getDirectionalColor() const;
		const glm::vec3& getAmbientColor() const;
	};
}
