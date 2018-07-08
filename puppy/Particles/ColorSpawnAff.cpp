#include "ColorSpawnAff.h"
namespace puppy
{
	void ColorSpawnAff::apply(std::list<Particle*>& p_toApply)
	{

		if (m_isRand)
		{
			for (Particle* p : p_toApply)
			{
				p->m_colorTint.r = m_min.r + ((m_max.r-m_min.r) * (float)rand() / (float)RAND_MAX);
				p->m_colorTint.g = m_min.g + ((m_max.g-m_min.g) * (float)rand() / (float)RAND_MAX);
				p->m_colorTint.b = m_min.b + ((m_max.b-m_min.b) * (float)rand() / (float)RAND_MAX);
			}
		}
		else
		{
			for (Particle* p : p_toApply)
			{
				p->m_colorTint.r = m_color.r;
				p->m_colorTint.g = m_color.g;
				p->m_colorTint.b = m_color.b;
			}
		}
	}
}