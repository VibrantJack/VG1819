#include "K_Renderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"

namespace kitten
{
	class CubeRenderable : public K_Renderable
	{
	private:
		puppy::Material* m_mat;

		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;

		void init(const char* p_pathToTexture);
	public:
		CubeRenderable(nlohmann::json& p_json);
		CubeRenderable(const char* p_pathToTex = nullptr);
		virtual ~CubeRenderable();

		void setTexture(const char* p_pathToTex);
		void render(kitten::Camera* p_cam) override;
	};
}