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
		const bool p_randomStart;

		float m_currentAnimationFrameTime;

		virtual void start() override;

		virtual bool hasUpdate() const override { return true; }
		virtual void update() override;

		void setRenderableTexture();

		void setRandomStartFrame();
	public:
		SpriteAnimator(const std::string& p_spriteName, bool p_randomStart);
		~SpriteAnimator();

		//This is only exists because units do not construct their gameobjects like everything else..
		//should be changed so this can be removed.
		//Setting this after start will result in bonked animations
		void setSpriteSheet(const std::string& p_characterName);


		void setAnimation(const std::string& p_animationName);
	};
}