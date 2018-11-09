#include "SpriteAnimator.h"
#include "kitten\K_GameObject.h"

namespace sprites
{
	SpriteAnimator::SpriteAnimator(const SpriteSheet* p_spriteSheet) : m_renderable(nullptr), m_spriteSheet(p_spriteSheet), m_currentAnimationFrameTime(0)
	{
		assert(m_spriteSheet != nullptr);
	}

	SpriteAnimator::~SpriteAnimator()
	{

	}

	void SpriteAnimator::start()
	{
		m_currentFrame = m_spriteSheet->getDefaultAnimation();

		m_renderable = m_attachedObject->getComponent<kitten::SpriteRenderable>();
		assert(m_renderable != nullptr);
		m_renderable->setupRenderable(m_spriteSheet->m_gridWidth / m_spriteSheet->m_sheetWidth, m_spriteSheet->m_gridHeight / m_spriteSheet->m_sheetHeight, *m_spriteSheet->m_material);

		m_time = kitten::K_Time::getInstance();
		assert(m_time != nullptr);

		setRenderableTexture();
	}

	void SpriteAnimator::setAnimation(const std::string& p_animationName)
	{
		m_currentFrame = m_spriteSheet->getAnimation(p_animationName);
		m_currentAnimationFrameTime = 0.0f;

		assert(m_currentFrame != nullptr);

		setRenderableTexture();
	}

	void SpriteAnimator::setRenderableTexture()
	{
		assert(m_currentFrame != nullptr);

		m_renderable->setTextureOffset(m_currentFrame->textureOffset);
	}

	void SpriteAnimator::update()
	{
		if (m_currentAnimationFrameTime > m_currentFrame->time)
		{
			// go to next frame
			m_currentFrame = m_currentFrame->next;

			m_currentAnimationFrameTime = 0.0f;

			setRenderableTexture();
		}
		else
		{
			m_currentAnimationFrameTime += m_time->getDeltaTime();
		}
	}
}