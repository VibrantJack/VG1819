#pragma once
#include "K_Renderable.h"
#include "puppy\TextureBlendMaterial.h"
#include "puppy\VertexEnvironment.h"

namespace kitten
{
	class SimpleQuadRenderable : public K_Renderable
	{
	private:
		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;

		puppy::Material* m_mat;

		bool m_isStatic, m_isRenderingStatic;
		puppy::Texture* m_staticTex;

		void addToStaticRender();

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	public:
		SimpleQuadRenderable(const std::string& p_texPath = "", bool p_isStatic = false);
		virtual ~SimpleQuadRenderable();

		void setTexture(const char* p_pathToTex);

		void render(const glm::mat4& p_viewProj) override;
	};
}
