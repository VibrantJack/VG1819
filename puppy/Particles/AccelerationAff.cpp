#include "AccelerationAff.h"
namespace puppy
{
	void AccelerationAff::apply(std::list<Particle*>& p_toApply, float p_delta)
	{
		if (!m_overLife)
		{
			if (m_isRand)
			{
				for (Particle* p : p_toApply)
				{
					p->m_velocity += p_delta * (m_min + (p->m_randFactor[AffRandKeys::accel] * (m_max-m_min)));
				}
			}
			else
			{
				for (Particle* p : p_toApply)
				{
					p->m_velocity += p_delta * m_accel;
				}
			}
		}
		else
		{
			for (Particle* p : p_toApply)
			{
				p->m_velocity = m_min + ((m_max-m_min) * (p->m_lived / p->m_lifetime));
			}
		}
		
	}
}