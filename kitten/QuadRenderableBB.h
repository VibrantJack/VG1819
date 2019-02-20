#pragma once
#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"
#include "K_Renderable.h"

namespace kitten
{
	class QuadRenderableBB : public K_Renderable
	{
	private:
		static puppy::VertexEnvironment* sm_vao;
		static unsigned int sm_instances;

		puppy::Material m_mat;

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	public:
		QuadRenderableBB(const char* p_pathToTexture = nullptr);
		~QuadRenderableBB();

		void setTexture(const char* p_pathToTexture);

		virtual void render(kitten::Camera* p_cam) override;
	};
}