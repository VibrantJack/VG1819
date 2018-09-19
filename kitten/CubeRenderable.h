#include "Renderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"

namespace kitten
{
	class CubeRenderable : public Renderable
	{
	private:
		puppy::Material* m_mat;

		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;
	public:
		CubeRenderable(const char* p_pathToTex = nullptr);
		virtual ~CubeRenderable();
		void setTexture(const char* p_pathToTex);
		void render(const glm::mat4& p_viewProj) override;
	};
}