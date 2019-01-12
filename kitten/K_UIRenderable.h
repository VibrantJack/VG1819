#pragma once

#include "puppy\P_Common.h"
#include "K_Component.h"
#include "Camera.h"

#include "puppy\Texture.h"
#include "puppy\P_UIRenderable.h"

// This is basically a shortcut now
// instead of extending the two classes below, can extend this
namespace kitten
{
	class K_UIRenderable : public K_Component, public puppy::P_UIRenderable
	{
	protected:
		K_UIRenderable();
		virtual ~K_UIRenderable();
	public:
		
		virtual void uiRender(Camera* p_cam) override = 0;
	};
}