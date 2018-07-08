#include "DirectionSpawnAff.h"
#include <iostream>
namespace puppy
{
	void DirectionSpawnAff::apply(std::list<Particle*>& p_toApply)
	{
		if (m_useOffset)
		{
			for (Particle* p : p_toApply)
			{
				p->m_direction = glm::normalize(p->m_offset);
			}
		}
		else
		{
			//Random direction
			for (Particle* p : p_toApply)
			{
				glm::vec3 dir = glm::vec3(rand() - (RAND_MAX / 2), rand() - (RAND_MAX / 2), rand() - (RAND_MAX / 2));
				dir = glm::normalize(dir);
				p->m_direction = dir;
			}
		}
	}
}