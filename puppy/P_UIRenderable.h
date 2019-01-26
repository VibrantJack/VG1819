#pragma once
#include "P_Common.h"
#include "Material.h"
#include "kitten\Camera.h"

namespace puppy
{
	class P_UIRenderable
	{
	public:
		virtual void uiRender(kitten::Camera* p_cam) = 0;

	protected:
		
	};
}