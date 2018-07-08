#pragma once
#include <list>
#include "Particle.h"
#include "SpawnAffector.h"
namespace puppy
{
	class ColorSpawnAff : public SpawnAffector
	{
	private:
		bool m_isRand;
		glm::vec3 m_min;
		glm::vec3 m_max;

		glm::vec3 m_color;
	public:
		ColorSpawnAff(const glm::vec3& p_color) : m_isRand(false), m_color(p_color) {};
		ColorSpawnAff(const glm::vec3& p_min, const glm::vec3& p_max) : m_isRand(true), m_min(p_min), m_max(p_max) {};

		virtual void apply(std::list<Particle*>& p_toApply);
	};
}