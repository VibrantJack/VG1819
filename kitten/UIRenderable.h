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

		void addToStaticUIRender(const puppy::Texture* p_texNeeded, puppy::TexturedVertex p_data[], int p_numElements);
		void addToDynamicUIRender();

		void removeFromStaticUIRender(const puppy::Texture* p_tex);
		void removeFromDynamicUIRender();
	public:
		
		virtual void uiRender(const glm::mat4& p_ortho) = 0;
	};
}