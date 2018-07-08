#include "Affector.h"
namespace puppy
{
	class RotationChangeAff : public Affector
	{
	private:
		float m_change;

		bool m_isRand;
		bool m_overLife;

		float m_min;
		float m_max;
	public:
		RotationChangeAff(float p_change) : m_isRand(false), m_change(p_change) {};
		RotationChangeAff(bool p_isOverLife, float p_min, float p_max) : m_isRand(true), m_min(p_min), m_max(p_max), m_overLife(p_isOverLife) {};

		virtual void apply(std::list<Particle*>& p_toApply, float p_delta) override;
	};
}