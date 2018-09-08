#pragma once

#include "puppy\P_Common.h"
#include "K_Component.h"
#include "Camera.h"

namespace kitten
{
	class Renderable : public K_Component
	{
	protected:
		Renderable();
		virtual ~Renderable();
	public:
		
		virtual void render(const glm::mat4& p_viewProj) = 0;
	};
}