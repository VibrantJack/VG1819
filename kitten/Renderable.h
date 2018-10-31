#pragma once

#include "puppy\P_Common.h"
#include "K_Component.h"
#include "Camera.h"
#include "puppy\Texture.h"

namespace kitten
{
	class Renderable : public K_Component
	{
	protected:
		Renderable();
		virtual ~Renderable();

		void addToStaticRender(const puppy::Texture* p_texNeeded, puppy::TexturedVertex p_data[], int p_numElements);
		void addToDynamicRender();

		void removeFromStaticRender(const puppy::Texture* p_tex);
		void removeFromDynamicRender();
	public:
		
		virtual void render(const glm::mat4& p_viewProj) = 0;
	};
}