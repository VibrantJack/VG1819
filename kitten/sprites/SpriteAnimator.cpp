#include "SpriteAnimator.h"
#include "kitten\K_GameObject.h"

namespace sprites
{
	SpriteAnimator::SpriteAnimator() : m_renderable(nullptr)
	{

	}

	SpriteAnimator::~SpriteAnimator()
	{

	}

	void SpriteAnimator::start()
	{
		m_renderable = m_attachedObject->getComponent<kitten::SpriteRenderable>();
		assert(m_renderable != nullptr);
	}

	void SpriteAnimator::update()
	{

	}
}