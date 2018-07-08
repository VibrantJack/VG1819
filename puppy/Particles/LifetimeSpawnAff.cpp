#include "LifetimeSpawnAff.h"

namespace puppy
{
	void LifetimeSpawnAff::apply(std::list<Particle*>& p_toApply)
	{
		if (m_isRand)
		{
			for (Particle* p : p_toApply)
			{
				p->m_lifetime = m_min + ((m_max-m_min) * ((float)rand() / RAND_MAX));
			}
		}
		else
		{
			for (Particle* p : p_toApply)
			{
				p->m_lifetime = m_killLength;
			}
		}
	}
}