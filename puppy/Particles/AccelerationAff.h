#include "Affector.h"
namespace puppy
{
	class AccelerationAff : public Affector
	{
	private:
		float m_accel;
		
		bool m_isRand;
		bool m_overLife;

		float m_min;
		float m_max;
	public:
		AccelerationAff(float p_accel) : m_isRand(false), m_accel(p_accel), m_overLife(false) {};
		AccelerationAff(bool p_overLife, float p_min, float p_max) : m_isRand(true), m_min(p_min), m_max(p_max), m_overLife(p_overLife) {};

		virtual void apply(std::list<Particle*>& p_toApply, float p_delta) override;
	};
}