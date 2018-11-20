#include "Affector.h"
#include "expressions\PostfixEval.h"
namespace puppy
{
	class PathAff : public Affector
	{
	public:
		enum PresetPathType {direction};
	private:
		bool m_isPreset;
		PresetPathType m_type;

		float m_scalar;

		float m_min;
		float m_max;

		postfix::PostfixEval* m_xEq;
		postfix::PostfixEval* m_yEq;
		postfix::PostfixEval* m_zEq;
	public:
		PathAff(PresetPathType p_type, float p_scalar) : m_isPreset(true), m_type(p_type), m_scalar(p_scalar) {};
		PathAff(postfix::PostfixEval* p_xEq, postfix::PostfixEval* p_yEq, postfix::PostfixEval* p_zEq);
		~PathAff();

		virtual void apply(std::list<Particle*>& p_toApply, float p_delta) override;
	};
}