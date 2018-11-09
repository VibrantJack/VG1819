#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_Time.h"
#include "SpriteRenderable.h"
#include "SpriteSheet.h"

namespace sprites
{
	class SpriteAnimator : public kitten::K_Component
	{
	private:
		kitten::SpriteRenderable* m_renderable;
		
		const SpriteSheet* m_spriteSheet;
		const SpriteSheet::AnimationFrame* m_currentFrame;
		const kitten::K_Time* m_time;

		float m_currentAnimationFrameTime;

		virtual void start() override;

		virtual bool hasUpdate() const override { return true; }
		virtual void update() override;

		void setRenderableTexture();
	public:
		SpriteAnimator(const std::string& p_spriteName);
		~SpriteAnimator();

		void setAnimation(const std::string& p_animationName);
	};
}