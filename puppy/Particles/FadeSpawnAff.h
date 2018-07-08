#pragma once
#include <list>
#include "SpawnAffector.h"
#include "Particle.h"
namespace puppy
{
	class FadeSpawnAff : public SpawnAffector
	{
	private:
		bool m_isRand;
		float m_min;
		float m_max;

		float m_fade;
	public:
		FadeSpawnAff(float p_fade) : m_isRand(false), m_fade(p_fade) {};
		FadeSpawnAff(float p_min, float p_max) : m_isRand(false), m_min(p_min), m_max(p_max) {};

		virtual void apply(std::list<Particle*>& p_toApply);
	};
}