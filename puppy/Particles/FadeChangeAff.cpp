#include "FadeChangeAff.h"
namespace puppy
{
	void FadeChangeAff::apply(std::list<Particle*>& p_toApply, float p_delta)
	{
		if (m_overLife)
		{
			for (Particle* p : p_toApply)
			{
				p->m_colorTint.a = m_min + (p->m_lived / p->m_lifetime) * (m_max-m_min);
			}
		}
		else
		{
			if (m_isRand)
			{
				for (Particle* p : p_toApply)
				{
					p->m_colorTint.a += p_delta * (m_min + (m_max * p->m_randFactor[AffRandKeys::fade]));
				}
			}
			else
			{
				for (Particle* p : p_toApply)
				{
					p->m_colorTint.a += p_delta * m_change;
				}
			}
		}
		
	}
}