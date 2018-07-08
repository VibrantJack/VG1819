#include "SizeSpawnAff.h"
namespace puppy
{
	void SizeSpawnAff::apply(std::list<Particle*>& p_toApply)
	{
		if (m_isRand)
		{
			for (Particle* p : p_toApply)
			{
				p->m_scale = m_min + ((m_max-m_min) * (float)rand()/(float)RAND_MAX);
			}
		}
		else
		{
			for (Particle* p : p_toApply)
			{
				p->m_scale = m_size;
			}
		}
	}
}