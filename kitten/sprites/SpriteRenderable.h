#pragma once
#include "kitten\Renderable.h"
#include "puppy\VertexEnvironment.h"
#include <unordered_map>

namespace kitten
{
	class SpriteRenderable : public Renderable
	{
	private:
		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	public:
		SpriteRenderable(const char* p_pathToSheet);
		virtual ~SpriteRenderable();

		virtual void render(const glm::mat4& p_viewProj) override;
	};
}