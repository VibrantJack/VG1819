#include "puppy\P_Common.h"
#include "K_Component.h"
#include "Camera.h"

namespace kitten
{
	class Renderable : public K_Component
	{
	public:
		Renderable();
		virtual ~Renderable();

		virtual void render(const glm::mat4& p_viewProj) = 0;
	};
}