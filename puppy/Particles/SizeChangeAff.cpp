#include "SizeChangeAff.h"
namespace puppy
{
	void SizeChangeAff::apply(std::list<Particle*>& p_toApply, float p_delta)
	{
		if (m_overLife)
		{
			for (Particle* p : p_toApply)
			{
				p->m_scale = m_min + ((p->m_lived / p->m_lifetime)*(m_max - m_min));
			}
		}
		else
		{
			if (m_isRand)
			{
				for (Particle* p : p_toApply)
				{
					p->m_scale += p_delta * (m_min + ((m_max-m_min) * p->m_randFactor[AffRandKeys::size]));
				}
			}
			else
			{
				for (Particle* p : p_toApply)
				{
					p->m_scale += p_delta * m_change;
				}
			}
		}
		
	}
}