#include "SpriteAnimator.h"
#include "kitten\K_GameObject.h"

namespace sprites
{
	SpriteAnimator::SpriteAnimator(const SpriteSheet* p_spriteSheet) : m_renderable(nullptr), m_spriteSheet(p_spriteSheet)
	{
		assert(m_spriteSheet != nullptr);
	}

	SpriteAnimator::~SpriteAnimator()
	{

	}

	void SpriteAnimator::start()
	{
		m_currentAnimation = m_spriteSheet->getDefaultAnimation();

		m_renderable = m_attachedObject->getComponent<kitten::SpriteRenderable>();
		assert(m_renderable != nullptr);
		m_renderable->m_mat = m_spriteSheet->m_material;

		m_time = kitten::K_Time::getInstance();
		assert(m_time != nullptr);

		setRenderableTexture();
	}

	void SpriteAnimator::setAnimation(const std::string& p_animationName)
	{
		m_currentAnimation = m_spriteSheet->getAnimation(p_animationName);
		m_currentAnimationFrameTime = 0.0f;

		assert(m_currentAnimation != nullptr);

		setRenderableTexture();
	}

	void SpriteAnimator::setRenderableTexture()
	{
		assert(m_currentAnimation != nullptr);

		//m_renderable->setTextureOffset(m_currentAnimation->offset);
	}

	void SpriteAnimator::update()
	{
		if (m_currentAnimationFrameTime > m_currentAnimation->time)
		{
			// go to next frame

			m_currentAnimationFrameTime = 0.0f;
		}
		else
		{
			m_currentAnimationFrameTime += m_time->getDeltaTime();
		}
	}
}