#include "K_ParticleSystem.h"
#include "puppy\Renderer.h"

namespace kitten
{
	K_ParticleSystem::K_ParticleSystem(const char* p_pathToEffectXML) : m_particleEffect(p_pathToEffectXML), m_time(nullptr)
	{

	}

	K_ParticleSystem::~K_ParticleSystem()
	{
		if (m_isEnabled)
		{
			onDisabled();
		}
	}

	void K_ParticleSystem::start()
	{
		m_time = K_Time::getInstance();
		assert(m_time != nullptr);

		puppy::Renderer::sm_instance->addParticleToRender(this);
	}

	void K_ParticleSystem::update()
	{
		m_particleEffect.update(m_time->getDeltaTime());
	}

	void K_ParticleSystem::onDisabled()
	{
		puppy::Renderer::sm_instance->removeParticleFromRender(this);
	}

	void K_ParticleSystem::onEnabled()
	{
		puppy::Renderer::sm_instance->addParticleToRender(this);
	}

	void K_ParticleSystem::pause()
	{
		m_particleEffect.pause();
	}

	void K_ParticleSystem::play()
	{
		m_particleEffect.play();
	}

	void K_ParticleSystem::stop()
	{
		m_particleEffect.stop();
	}

	void K_ParticleSystem::refreshXML()
	{
		m_particleEffect.refreshXML();
	}

	void K_ParticleSystem::render(const glm::mat4& p_viewInverse, const glm::mat4& p_viewProj)
	{
		m_particleEffect.render(p_viewInverse, p_viewProj);
	}
}