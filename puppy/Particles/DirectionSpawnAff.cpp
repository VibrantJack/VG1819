#include "DirectionSpawnAff.h"
#include <iostream>
namespace puppy
{
	void DirectionSpawnAff::apply(std::list<Particle*>& p_toApply)
	{
		switch (m_mode)
		{
		case random:
			//Random direction
			for (Particle* p : p_toApply)
			{
				glm::vec3 dir = glm::vec3(rand() - (RAND_MAX / 2), rand() - (RAND_MAX / 2), rand() - (RAND_MAX / 2));
				dir = glm::normalize(dir);
				p->m_direction = dir;
			}

			break;
		case offset:

			for (Particle* p : p_toApply)
			{
				p->m_direction = glm::normalize(p->m_offset);
			}

			break;

		case up:

			for (Particle* p : p_toApply)
			{
				p->m_direction = glm::vec3(0, 1, 0);
			}

			break;
		}
	}
}