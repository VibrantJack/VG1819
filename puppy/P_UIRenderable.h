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
		void addToStaticUIRender(const Material& p_mat, TexturedVertex p_data[], int p_numElements);
		void addToDynamicUIRender();

		void removeFromStaticUIRender(const Material& p_mat);
		void removeFromDynamicUIRender();
	};
}