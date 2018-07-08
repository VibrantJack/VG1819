#include "FadeSpawnAff.h"
namespace puppy
{
	void FadeSpawnAff::apply(std::list<Particle*>& p_toApply)
	{
		if (m_isRand)
		{
			for (Particle* p : p_toApply)
			{
				p->m_colorTint.a = m_min + ((m_max-m_min) * (float)rand()/(float)RAND_MAX);
			}
		}
		else
		{
			for (Particle* p : p_toApply)
			{
				p->m_colorTint.a = m_fade;
			}
		}
	}
}