#pragma once
#include "kitten\K_Component.h"
#include "SpriteRenderable.h"

namespace sprites
{
	class SpriteAnimator : kitten::K_Component
	{
	private:
		kitten::SpriteRenderable* m_renderable;

		virtual void start() override;

		virtual bool hasUpdate() const override { return true; }
		virtual void update() override;

	public:
		SpriteAnimator();
		~SpriteAnimator();
	};
}