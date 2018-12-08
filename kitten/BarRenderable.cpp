#include "BarRenderable.h"

namespace kitten
{
	puppy::VertexEnvironment* BarRenderable::sm_vao = nullptr;
	unsigned int BarRenderable::instances = 0;


	BarRenderable::BarRenderable(const char* p_pathToTexture) : m_mat(puppy::ShaderType::basic)
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

			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 6);
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

		sm_vao->drawArrays(GL_TRIANGLES);
	}
}