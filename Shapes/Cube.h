#pragma once

/*
	Callum MacKenzie
	A renderable cube.
	Only supports one colour pattern for convenience
*/

#include "puppy\RenderableNode.h"
#include "puppy\VertexEnvironment.h"
#include "puppy\Texture.h"

namespace shapes
{
	class Cube : public puppy::RenderableNode
	{
	private:
		static puppy::VertexEnvironment* sm_vao;
		puppy::Texture* m_tex;

	public:
		Cube(const char* p_pathToTexture);
		~Cube();

		void render(const glm::mat4& p_viewProj) override;
		void update(float p_deltaTime) override;
	};
}

