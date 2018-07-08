#pragma once

#include "puppy\P_Common.h"

namespace puppy
{
	enum AffRandKeys { accel, color, fade, size, path, AFF_RAND_SIZE_MAX = path+1 };

	struct Particle
	{
		glm::vec3 m_centerPoint;		

		float m_lived;
		float m_lifetime;

		float m_pathProgress;
		float m_velocity;
		
		float m_rotation;

		float m_randFactor[AFF_RAND_SIZE_MAX]; // holds values from 0 to 1


		glm::vec3 m_direction;
		glm::vec3 m_offset;
		glm::vec4 m_colorTint;
		glm::vec2 m_scale;
		Particle() : m_lived(0), m_velocity(0), m_direction(0, 0, 0), m_colorTint(0,0,0,0), m_scale(1,1), m_centerPoint(0,0,0), m_pathProgress(0), m_lifetime(-1), m_rotation(0) {}
	};
}