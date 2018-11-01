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
		glm::vec4 m_colorTint;
		bool m_isStatic;

		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;

		void addToStaticRender();

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	public:
		QuadRenderable(const char* p_pathToTex = nullptr, bool p_isStatic = false);
		virtual ~QuadRenderable();

		void setTexture(const char* p_pathToTex);
		void setColorTint(const glm::vec4& p_vec4);
		glm::vec4 getColorTint() { return m_colorTint; }
		void render(const glm::mat4& p_viewProj) override;
	};
}