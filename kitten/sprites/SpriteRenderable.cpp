#include "SpriteRenderable.h"
#include "puppy\ShaderManager.h"
#include "kitten\K_GameObject.h"
#include "SpriteAnimator.h"

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

	void SpriteRenderable::setupRenderable(const float& p_uWidth, const float& p_vHeight, const float& p_characterWidth, const float& p_characterHeight, puppy::Material& p_mat)
	{
		m_mat = &p_mat;

		float vertXWidth = (p_characterWidth / p_characterHeight) - 0.5f;

		puppy::TexturedVertex verts[] =
		{
			{ -vertXWidth, -0.5f, 0.0f,		p_uWidth, 1.0f - p_vHeight }, //bottom left
			{ -vertXWidth,  0.5f, 0.0f,		p_uWidth, 1.0f}, //top left
			{ vertXWidth,  0.5f, 0.0f,		0.0f, 1.0f}, //top right
			{ vertXWidth,  0.5f, 0.0f,		0.0f, 1.0f }, //top right
			{ vertXWidth, -0.5f, 0.0f,		0.0f, 1.0f - p_vHeight }, //bottom right
			{ -vertXWidth, -0.5f, 0.0f,		p_uWidth, 1.0f - p_vHeight }, //bottom  left
		};

		m_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::sprite), 6);
	}

	void SpriteRenderable::start()
	{
		addToDynamicRender();

		auto animator = m_attachedObject->getComponent<sprites::SpriteAnimator>();
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