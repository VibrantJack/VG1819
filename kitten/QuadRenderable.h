#include "Renderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"

namespace kitten
{
	class QuadRenderable : public Renderable
	{
	private:
		puppy::Material* m_mat;
		puppy::Texture* m_tex;
		bool m_isStatic;



		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;
	public:
		QuadRenderable(const char* p_pathToTex = nullptr, bool p_isStatic = false);
		virtual ~QuadRenderable();

		virtual void start() override;

		void setTexture(const char* p_pathToTex);
		void render(const glm::mat4& p_viewProj) override;
	};
}