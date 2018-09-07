#pragma once
#include "puppy\P_Common.h"
#include "puppy\RenderableNode.h"
#include "puppy\VertexEnvironment.h"
#include "../SceneManagement/Frustum.h"
#include "puppy\Texture.h"

namespace shapes
{
	class RenderableFrustum : public puppy::RenderableNode
	{
	private:
		puppy::VertexEnvironment* m_vao;
		static puppy::Texture* sm_tex;

	public:
		RenderableFrustum();
		~RenderableFrustum();

		void setPoints(const glm::vec3& p_ftl, const glm::vec3& p_ftr, const glm::vec3& p_fbl, const glm::vec3& p_fbr, const glm::vec3& p_ntl,
			const glm::vec3& p_ntr, const glm::vec3& p_nbl, const glm::vec3& p_nbr);

		void render(const glm::mat4& p_viewProj) override;
		void update(float p_deltaTime) override;
	};
}