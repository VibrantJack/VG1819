#pragma once

#include "puppy\P_Common.h"
#include "K_Component.h"
#include "Camera.h"
#include "puppy\Texture.h"

namespace kitten
{
	class UIRenderable : public K_Component
	{
	protected:
		UIRenderable();
		virtual ~UIRenderable();

		void addToStaticRender(const puppy::Texture* p_texNeeded, puppy::TexturedVertex p_data[], int p_numElements);
		void addToDynamicRender();

		void removeFromStaticRender(const puppy::Texture* p_tex);
		void removeFromDynamicRender();
	public:
		
		virtual void render(const glm::mat4& p_ortho) = 0;
	};
}