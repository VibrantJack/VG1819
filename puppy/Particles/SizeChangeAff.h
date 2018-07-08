#include "Affector.h"
namespace puppy
{
	class SizeChangeAff : public Affector
	{
	private:
		glm::vec2 m_change;

		bool m_isRand;
		bool m_overLife;

		glm::vec2 m_min;
		glm::vec2 m_max;
	public:
		SizeChangeAff(const glm::vec2& p_change) : m_isRand(false), m_change(p_change) {};
		SizeChangeAff(bool p_isOverLife, const glm::vec2& p_min, const glm::vec2& p_max) : m_isRand(true), m_min(p_min), m_max(p_max), m_overLife(p_isOverLife) {};

		virtual void apply(std::list<Particle*>& p_toApply, float p_delta) override;
	};
}