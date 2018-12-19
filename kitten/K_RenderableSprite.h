#include "K_Renderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"

namespace kitten
{
	class K_RenderableSprite : public K_Renderable
	{
	private:
		puppy::Material* m_mat;
		puppy::Texture* m_tex;

		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;
	public:
		K_RenderableSprite(const char* p_pathToTex = nullptr);
		virtual ~K_RenderableSprite();

		void setTexture(const char* p_pathToTex);
		void render(const glm::mat4& p_viewProj) override;
	};
}
