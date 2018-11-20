#pragma once
#include "K_Component.h"
#include "kitten\K_Time.h"

#include "puppy\Particles\Effect.h"

namespace kitten
{
	class K_ParticleSystem : public K_Component
	{
	private:
		puppy::Effect m_particleEffect;
		K_Time* m_time;
		bool m_isPlaying;

	public:
		K_ParticleSystem(const char* p_pathToEffectXML);
		~K_ParticleSystem();

		virtual bool hasUpdate() const override { return true; }
		virtual void update() override;

		virtual void start() override;

		virtual void onDisabled() override;
		virtual void onEnabled() override;

		bool isPlaying() const;

		void pause();
		void play();
		void stop();

		void refreshXML();

		void render(const glm::mat4& p_viewInverse, const glm::mat4& p_viewProj);
	};
}