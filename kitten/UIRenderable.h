#pragma once

#include "puppy\P_Common.h"
#include "K_Component.h"
#include "Camera.h"

namespace kitten
{
	class UIRenderable : public K_Component
	{
	protected:
		UIRenderable();
		virtual ~UIRenderable();
	public:
		
		virtual void render(const glm::mat4& p_ortho) = 0;
	};
}