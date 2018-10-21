#pragma once
#include "AudioEngineWrapper.h"
#include "kitten\K_Component.h"
#include "kitten\Transform.h"

namespace kitten
{
	class AudioListener : public K_Component, public TransformPositionListener
	{
	private:
		Transform* m_cachedTransform;
	public:
		AudioListener();
		~AudioListener();

		void start() override;

		void onPosChanged(const glm::vec3& p_newPos) override;
	};
}