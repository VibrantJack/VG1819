#pragma once
#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"
#include "K_Renderable.h"

namespace kitten
{
	class BarRenderable : public K_Renderable
	{
	private:
		static puppy::VertexEnvironment* sm_vao;
		static unsigned int instances;

		bool m_isHealthBar;
		puppy::Material m_mat;
		float m_startXScale;

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	public:
		BarRenderable(const char* p_pathToTexture = nullptr, bool p_isHealthBar = false);
		~BarRenderable();

		void setTexture(const char* p_pathToTexture);
		void setIsHealthBar(bool p_isHealthbar) { m_isHealthBar = p_isHealthbar; }

		virtual void render(kitten::Camera* p_cam) override;
	};
}