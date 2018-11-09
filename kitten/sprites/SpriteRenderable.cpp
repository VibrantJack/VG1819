#include "SpriteRenderable.h"
#include "puppy\ShaderManager.h"
#include "kitten\K_GameObject.h"

namespace kitten
{
	SpriteRenderable::SpriteRenderable() : m_mat(nullptr), m_vao(nullptr)
	{
		//VAO and material set in by SpriteAnimator according to the sprite sheet
	}

	SpriteRenderable::~SpriteRenderable()
	{
		if (m_isEnabled)
		{
			removeFromDynamicRender();
		}

		//Material deleted by sprite loader
	}

	void SpriteRenderable::setupRenderable(const float& p_x, const float& p_y, puppy::Material& p_mat)
	{
		m_mat = &p_mat;

		puppy::TexturedVertex verts[] =
		{
			{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
			{ -0.5f,  0.0f, 0.5f,		0.0f, p_y },
			{ 0.5f,  0.0f, 0.5f,		p_x, p_y },
			{ 0.5f,  0.05f, 0.5f,		p_x, p_y },
			{ 0.5f, 0.0f, 0.5f,			p_x, 0.0f },
			{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f }
		};

		m_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::sprite), 6);
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
		m_vao->drawArrays(GL_TRIANGLES);
	}
}