#pragma once
#include "K_Renderable.h"
#include "puppy\TextureBlendMaterial.h"
#include "puppy\VertexEnvironment.h"

namespace kitten
{
	class QuadRenderable : public K_Renderable
	{
	private:
		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;

		puppy::TextureBlendMaterial m_mat;

		bool m_isStatic, m_isRenderingStatic;
		puppy::Texture* m_staticTex;

		void addToStaticRender();

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	public:
		QuadRenderable(const std::string& p_texPath ="", bool p_isStatic = false);
		virtual ~QuadRenderable();

		void setTexture(const char* p_pathToTex);

		void addTexture(puppy::Texture* p_tex, const float& p_weight = 1.0f);
		void removeTexture(puppy::Texture* p_tex);

		void changeWeight(puppy::Texture* p_tex, const float& p_weight);

		void render(const glm::mat4& p_viewProj) override;
	};
}