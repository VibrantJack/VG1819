#include "OffsetSpawnAff.h"
#include <iostream>
namespace puppy
{
	void OffsetSpawnAff::apply(std::list<Particle*>& p_toApply)
	{
		switch (m_mode)
		{
		case point:
			for (Particle* p : p_toApply)
			{
				p->m_centerPoint = m_offset;
				p->m_offset = p->m_centerPoint;
			}
			break;
		case disc:
			for (Particle* p : p_toApply)
			{
				//set position as if this was a point emitter
				p->m_centerPoint = m_offset;
				//get random offset (within circle)
				float scale =  m_radius * ((float)rand() / (float)RAND_MAX);
				glm::vec3 position = glm::vec3(rand() - (RAND_MAX/2), 0, rand() - (RAND_MAX/2));
				position = glm::normalize(position);
				position *= scale;
				//add offset
				p->m_centerPoint += position;
				p->m_offset = p->m_centerPoint;
			}
			break;
		case sphere:
			for (Particle* p : p_toApply)
			{
				p->m_centerPoint = m_offset;
				//get random offset (within sphere)
				float scale = m_radius * ((float)rand() / (float)RAND_MAX);
				glm::vec3 position = glm::vec3(rand() - (RAND_MAX / 2), rand() - (RAND_MAX/2), rand() - (RAND_MAX / 2));
				position = glm::normalize(position);
				position *= scale;
				//add offset
				p->m_centerPoint += position;
				p->m_offset = p->m_centerPoint;

			}
			break;
		case box:
			for (Particle* p : p_toApply)
			{
				//Not supported yet
				p->m_centerPoint = m_offset;
				p->m_offset = p->m_centerPoint;
			}
			break;
		}
	}
}