#include "VelocitySpawnAff.h"
namespace puppy
{
	void VelocitySpawnAff::apply(std::list<Particle*>& p_toApply)
	{
		if (m_isRand)
		{
			for (Particle* p : p_toApply)
			{
				p->m_velocity = m_min + ((m_max-m_min) * (float)rand() / (float)RAND_MAX);
			}
		}
		else
		{
			for (Particle* p : p_toApply)
			{
				p->m_velocity = m_vel;
			}
		}
	}
}