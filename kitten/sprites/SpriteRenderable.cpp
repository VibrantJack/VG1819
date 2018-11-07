#include "SpriteRenderable.h"
#include "puppy\ShaderManager.h"

namespace kitten
{
	int SpriteRenderable::sm_instances = 0;
	puppy::VertexEnvironment* SpriteRenderable::sm_vao = nullptr;

	SpriteRenderable::SpriteRenderable() : m_mat(nullptr)
	{
		if (sm_instances < 1)
		{
			puppy::TexturedVertex verts[] = 
			{
				{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
				{ -0.5f,  0.0f, 0.5f,		0.0f, 1.0f },
				{ 0.5f,  0.0f, 0.5f,		1.0f, 1.0f },
				{ 0.5f,  0.05f, 0.5f,		1.0f, 1.0f },
				{ 0.5f, 0.0f, 0.5f,			1.0f, 0.0f },
				{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f }
			};

			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);
		}

		++sm_instances;
	}

	SpriteRenderable::~SpriteRenderable()
	{
		if (m_isEnabled)
		{
			removeFromDynamicRender();
		}

		--sm_instances;
		if (sm_instances == 0)
		{
			delete sm_vao;
		}
	}

	void SpriteRenderable::start()
	{
		addToDynamicRender();
	}

	void SpriteRenderable::onEnabled()
	{
		addToDynamicRender();
	}

	void SpriteRenderable::onDisabled()
	{
		removeFromDynamicRender();
	}

	void SpriteRenderable::render(const glm::mat4& p_viewProj)
	{
		assert(m_mat != nullptr);
		m_mat->apply();

		//Set world matrix
		glm::mat4 wvp = p_viewProj * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		//Set texture offset
		

		//render
		sm_vao->drawArrays(GL_TRIANGLES);
	}
}