#include "PathAff.h"
namespace puppy
{
	PathAff::PathAff(postfix::PostfixEval* p_xEq, postfix::PostfixEval* p_yEq, postfix::PostfixEval* p_zEq)
		: m_isPreset(false), m_xEq(p_xEq), m_yEq(p_yEq), m_zEq(p_zEq)
	{

	}

	PathAff::~PathAff()
	{
		delete m_xEq;
		delete m_yEq;
		delete m_zEq;
	}

	void PathAff::apply(std::list<Particle*>& p_toApply, float p_delta)
	{
		if (m_isPreset)
		{
			switch (m_type)
			{
			case direction:
				for (Particle* p : p_toApply)
				{
					p->m_centerPoint += p->m_direction * p->m_velocity * p_delta * m_scalar;
				}
				break;
			}
		}
		else
		{
			//Use equations. Should probably only be used for finding new 
			//paths / experimenting -- much slower than coded-in expressions
			for (Particle* p : p_toApply)
			{
				p->m_pathProgress += p->m_velocity * p_delta;
				float xRes = m_xEq->getResult(p->m_pathProgress, p->m_centerPoint.x, p->m_centerPoint.y, p->m_centerPoint.z, p_delta);
				float yRes = m_yEq->getResult(p->m_pathProgress, p->m_centerPoint.x, p->m_centerPoint.y, p->m_centerPoint.z, p_delta);
				float zRes = m_zEq->getResult(p->m_pathProgress, p->m_centerPoint.x, p->m_centerPoint.y, p->m_centerPoint.z, p_delta);
				p->m_centerPoint = glm::vec3(xRes, yRes, zRes) + p->m_offset;
			}
		}
	}
}