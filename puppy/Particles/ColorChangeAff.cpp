#include "ColorChangeAff.h"
namespace puppy
{
	void ColorChangeAff::apply(std::list<Particle*>& p_toApply, float p_delta)
	{
		if (m_overLife)
		{
			for (Particle* p : p_toApply)
			{
				p->m_colorTint = glm::vec4(m_min + (p->m_lived/p->m_lifetime) * (m_max-m_min) , p->m_colorTint.a);
			}
		}
		else
		{
			if (m_isRand)
			{
				for (Particle* p : p_toApply)
				{
					glm::vec3 col = glm::vec3(p_delta * (m_min + ((m_max - m_min) * p->m_randFactor[AffRandKeys::color])));
					p->m_colorTint += glm::vec4(col, 0);
				}
			}
			else
			{
				for (Particle* p : p_toApply)
				{
					p->m_colorTint += glm::vec4(p_delta * m_color, 0);
				}
			}
		}
		
	}
}