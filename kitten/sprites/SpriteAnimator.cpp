#include "SpriteAnimator.h"
#include "kitten\K_GameObject.h"
#include "kibble\sprites\SpriteLoader.h"

namespace sprites
{
	SpriteAnimator::SpriteAnimator(const std::string& p_spriteName) : m_renderable(nullptr), m_currentAnimationFrameTime(0)
	{
		m_spriteSheet = kibble::SpriteLoader::sm_instance->getSpriteSheet(p_spriteName);
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
		float uMax = (float)m_spriteSheet->m_characterWidth / m_spriteSheet->m_sheetWidth;
		float vMax = (float)m_spriteSheet->m_characterHeight / m_spriteSheet->m_sheetHeight;
		m_renderable->setupRenderable(uMax, vMax, m_spriteSheet->m_characterWidth, m_spriteSheet->m_characterHeight, *m_spriteSheet->m_material);

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