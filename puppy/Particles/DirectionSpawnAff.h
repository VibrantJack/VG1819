#pragma once
#include <list>
#include "SpawnAffector.h"
#include "Particle.h"
#include "Emitter.h"
namespace puppy
{
	class DirectionSpawnAff : public SpawnAffector
	{
	private:
		bool m_useOffset;
	public:
		DirectionSpawnAff(bool p_useOffset) : m_useOffset(p_useOffset) {}

		virtual void apply(std::list<Particle*>& p_toApply);
	};
}