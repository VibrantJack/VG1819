#pragma once
#include "P_Common.h"
#include "Material.h"

namespace puppy
{
	class P_Renderable
	{
	protected:
		void addToStaticRender(const Material& p_mat, TexturedVertex p_data[], int p_numElements);
		void addToDynamicRender();

		void removeFromStaticRender(const Material& p_mat);
		void removeFromDynamicRender();
	public:
		virtual void render(const glm::mat4& p_viewProj) = 0;
	};
}
