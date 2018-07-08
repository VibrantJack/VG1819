#include "SpawnAffector.h"
namespace puppy
{
	class LifetimeSpawnAff : public SpawnAffector
	{
	private:
		float m_killLength;

		bool m_isRand;
		
		float m_min;
		float m_max;

	public:
		LifetimeSpawnAff(float p_killLength) : m_isRand(false), m_killLength(p_killLength) {};
		LifetimeSpawnAff(float p_min, float p_max) : m_isRand(true), m_min(p_min), m_max(p_max) {};

		virtual void apply(std::list<Particle*>& p_toApply) override;
	};
}