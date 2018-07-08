#pragma once

#include "Particle.h"
#include <list>

//Interface class for affectors
namespace puppy
{
	class Affector
	{
	
	public:
		//Affector() {}
		//virtual ~Affector() {}

		virtual void apply(std::list<struct Particle*>& p_toApply, float p_delta)=0;
	};
}