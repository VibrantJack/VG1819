#include "SpriteRenderable.h"
#include "puppy\ShaderManager.h"
#include "kitten\K_GameObject.h"

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

			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::sprite), 6);
		}

		//Material is set in SpriteAnimator.cpp

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

		auto animator = m_attachedObject->getComponent<SpriteRenderable>();
		assert(animator != nullptr); //Every SpriteRenderable needs a sprite animator!
	}

	void SpriteRenderable::onEnabled()
	{
		addToDynamicRender();
	}

	void SpriteRenderable::onDisabled()
	{
		removeFromDynamicRender();
	}

	void SpriteRenderable::setTextureOffset(const glm::vec2& p_offset)
	{
		m_texOffset = p_offset;
	}

	void SpriteRenderable::render(const glm::mat4& p_viewProj)
	{
		assert(m_mat != nullptr);
		m_mat->apply();

		//Set world matrix
		glm::mat4 wvp = p_viewProj * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		//Set texture offset
		m_mat->setUniform(TEXTURE_OFFSET_UNIFORM_NAME, m_texOffset);

		//render
		sm_vao->drawArrays(GL_TRIANGLES);
	}
}