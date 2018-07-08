#pragma once

#include "Particle.h"
#include <list>

//Class that applies a single property to a list of particles
namespace puppy
{
	class SpawnAffector
	{	
	public:
		//SpawnAffector() {}
		//virtual ~SpawnAffector() {}

		virtual void apply(std::list<struct Particle*>& p_toApply) = 0;
	};
}