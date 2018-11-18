#include "Renderable.h"
#include "puppy\TextureBlendMaterial.h"
#include "puppy\VertexEnvironment.h"

namespace kitten
{
	class QuadRenderable : public Renderable
	{
	private:
		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;

		puppy::TextureBlendMaterial* m_mat;

		bool m_isStatic;
		puppy::Texture* m_tex;
		

		void addToStaticRender();

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	public:
		QuadRenderable(const std::string& p_texPath ="", bool p_isStatic = false);
		virtual ~QuadRenderable();

		void setTexture(const char* p_pathToTex);

		void addTexture(const char* p_pathToTex, const float& p_weight);
		void removeTexture(const char* p_pathToTex);

		void changeWeight(const char* p_pathToTex, const float& p_weight);

		void render(const glm::mat4& p_viewProj) override;
	};
}