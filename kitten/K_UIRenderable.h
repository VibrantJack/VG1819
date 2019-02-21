#pragma once

#include "puppy\P_Common.h"
#include "puppy\Material.h"
#include "puppy\Texture.h"
#include "puppy\P_UIRenderable.h"

#include "K_Component.h"
#include "Camera.h"

#include <vector>

//////////////////////////
// This is basically a shortcut now
// instead of extending the two classes below, can extend this
//////////////////////////
// ^ changed for UI sorting, no longer true. 
// this is the uirenderable -- P_UIRenderable is not used... I think
// - Callum

namespace kitten
{
	class K_RenderNode;

	class K_UIRenderable : public K_Component, public puppy::P_UIRenderable
	{
		friend class K_RenderNode;
	private:
		K_RenderNode* m_cachedRenderNode;

	protected:
		K_UIRenderable();
		virtual ~K_UIRenderable();

		void addToStaticUIRender(const puppy::Material& p_mat, puppy::TexturedVertex p_data[], int p_numElements);
		void addToDynamicUIRender();
		void addToDynamicTransparentUIRender();

		void removeFromStaticUIRender(const puppy::Material& p_mat);
		void removeFromDynamicUIRender();
		void removeFromDynamicTransparentUIRender();
	public:
		
		virtual void uiRender(Camera* p_cam) = 0;
	};
}