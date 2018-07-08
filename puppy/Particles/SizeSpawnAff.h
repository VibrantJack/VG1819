#pragma once
#include <list>
#include "SpawnAffector.h"
#include "Particle.h"
namespace puppy
{
	class SizeSpawnAff : public SpawnAffector
	{
	private:
		bool m_isRand;
		glm::vec2 m_min;
		glm::vec2 m_max;

		glm::vec2 m_size;
	public:
		SizeSpawnAff(const glm::vec2& p_size) : m_isRand(false), m_size(p_size) {};
		SizeSpawnAff(const glm::vec2& p_min, const glm::vec2& p_max) : m_isRand(true), m_min(p_min), m_max(p_max) {};

		virtual void apply(std::list<Particle*>& p_toApply);
	};
}