#pragma once
#include "P_Common.h"
#include "Material.h"
#include "kitten\Camera.h"

namespace puppy
{
	class P_Renderable
	{
	protected:
		void addToStaticRender(const Material& p_mat, const TexturedVertex p_data[], int p_numElements);
		void addToStaticRender(const Material& p_mat, const NormalVertex p_data[], const std::vector<unsigned int>* p_indices, int p_numElements);
		void addToDynamicRender();

		void removeFromStaticRender(const Material& p_mat, bool p_usedNormals = false);
		void removeFromDynamicRender();
	public:
		virtual void render(kitten::Camera* p_cam) = 0;
	};
}
