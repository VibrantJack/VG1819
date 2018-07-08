#pragma once
#include <list>
#include "SpawnAffector.h"
#include "Particle.h"
namespace puppy
{
	class VelocitySpawnAff : public SpawnAffector
	{
	private:
		bool m_isRand;
		float m_min;
		float m_max;

		float m_vel;
	public:
		VelocitySpawnAff(float p_vel) : m_isRand(false), m_vel(p_vel) {};
		VelocitySpawnAff(float p_min, float p_max) : m_isRand(true), m_min(p_min), m_max(p_max) {};

		virtual void apply(std::list<Particle*>& p_toApply);
	};
}