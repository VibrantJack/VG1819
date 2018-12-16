#include "BarRenderable.h"

namespace kitten
{
	puppy::VertexEnvironment* BarRenderable::sm_vao = nullptr;
	unsigned int BarRenderable::instances = 0;


	BarRenderable::BarRenderable(const char* p_pathToTexture) : m_mat(puppy::ShaderType::basic_u_scale), m_uScale(1.0f)
	{
		if (instances == 0)
		{
			puppy::TexturedVertex verts[] =
			{
				{ 0.0f, -0.5f, 0.0f,		0.0f, 0.0f },
				{ 0.0f,  0.5f, 0.0f,		0.0f, 1.0f },
				{ 1.0f,  0.5f, 0.0f,		1.0f, 1.0f },
				{ 1.0f,  0.5f, 0.0f,		1.0f, 1.0f },
				{ 1.0f, -0.5f, 0.0f,		1.0f, 0.0f },
				{ 0.0f, -0.5f, 0.0f,		0.0f, 0.0f }
			};

			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic_u_scale), 6);
		}

		++instances;

		if (p_pathToTexture != nullptr)
		{
			m_mat.setTexture(p_pathToTexture);
		}
		
	}

	BarRenderable::~BarRenderable()
	{
		--instances;

		if (instances == 0)
		{
			delete sm_vao;
			sm_vao = nullptr;
		}

		if (m_isEnabled)
		{
			onDisabled();
		}
	}

	void BarRenderable::setTexture(const char* p_pathToTexture)
	{
		m_mat.setTexture(p_pathToTexture);
	}

	void BarRenderable::setUScale(const float& p_uScale)
	{
		m_uScale = 1/p_uScale;
	}

	void BarRenderable::start()
	{
		onEnabled();
	}

	void BarRenderable::onEnabled()
	{
		addToDynamicRender();
	}

	void BarRenderable::onDisabled()
	{
		removeFromDynamicRender();
	}

	void BarRenderable::render(const glm::mat4& p_viewProj)
	{
		m_mat.apply();
		m_mat.setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, p_viewProj * getTransform().getWorldTransform());
		m_mat.setUniform("xScale", getTransform().getLocalScale().x);
		m_mat.setUniform("uScale", m_uScale);

		sm_vao->drawArrays(GL_TRIANGLES);
	}
}