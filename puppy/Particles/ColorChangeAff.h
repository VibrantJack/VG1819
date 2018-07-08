#include "Affector.h"
namespace puppy
{
	class ColorChangeAff : public Affector
	{
	private:
		glm::vec3 m_color;

		bool m_isRand;
		bool m_overLife;

		glm::vec3 m_min;
		glm::vec3 m_max;
	public:
		ColorChangeAff(const glm::vec3& p_color) : m_isRand(false), m_color(p_color), m_overLife(false) {};
		ColorChangeAff(bool p_isOverLife, const glm::vec3& p_min, const glm::vec3& p_max) : m_isRand(true), m_min(p_min), m_max(p_max), m_overLife(p_isOverLife) {};

		virtual void apply(std::list<Particle*>& p_toApply, float p_delta) override;
	};
}