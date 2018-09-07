#include "K_Component.h"

namespace kitten
{
	class Renderable : public K_Component
	{
	public:
		Renderable();
		virtual ~Renderable();

		virtual void Render() = 0;
	};
}