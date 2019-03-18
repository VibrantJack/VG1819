#pragma once
#include <list>
#include "SpawnAffector.h"
#include "Particle.h"
#include "Emitter.h"
namespace puppy
{
	class DirectionSpawnAff : public SpawnAffector
	{
	public:
		enum mode
		{
			offset,
			up,
			random,
			down,
			left
		};
	private:
		bool m_mode;
	public:
		DirectionSpawnAff(mode p_mode) : m_mode(p_mode) {}

		virtual void apply(std::list<Particle*>& p_toApply);
	};
}