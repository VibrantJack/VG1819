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
		static puppy::VertexEnvironment* sm_upRightVao;
		static int sm_instances, sm_upRightInstances;

		puppy::Material* m_mat;

		bool m_isStatic, m_isRenderingStatic, m_isUpright;
		puppy::Texture* m_staticTex;

		void addToStaticRender();

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	public:
		SimpleQuadRenderable(const std::string& p_texPath = "", bool p_isStatic = false, bool p_upRight = false);
		virtual ~SimpleQuadRenderable();

		void setTexture(const char* p_pathToTex);

		void render(const glm::mat4& p_viewProj) override;
	};
}
