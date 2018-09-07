#pragma once

#include "puppy\P_Common.h"
#include "puppy\Texture.h"
#include "puppy\VertexEnvironment.h"
#include "puppy\RenderableNode.h"

namespace shapes
{
	class Rectangle : public puppy::RenderableNode
	{
	private:
		static puppy::VertexEnvironment* sm_vao;
		puppy::Texture* m_tex;
		
	public:
		Rectangle(const char* p_pathToTex);
		~Rectangle();

		void render(const glm::mat4& p_viewProj) override;
		void update(float p_deltaTime) override;
	};
}