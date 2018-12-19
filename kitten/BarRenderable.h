#pragma once
#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"
#include "Renderable.h"

namespace kitten
{
	class BarRenderable : public Renderable
	{
	private:
		static puppy::VertexEnvironment* sm_vao;
		static unsigned int instances;

		puppy::Material m_mat;
		float m_uScale;

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	public:
		BarRenderable(const char* p_pathToTexture = nullptr);
		~BarRenderable();

		void setTexture(const char* p_pathToTexture);
		void setUScale(const float& p_scale);

		virtual void render(const glm::mat4& p_viewProj) override;
	};
}