#include "K_ParticleSystem.h"
#include "puppy\Renderer.h"

namespace kitten
{
	K_ParticleSystem::K_ParticleSystem(const std::string& p_pathToXML) : m_time(nullptr), m_isPlaying(false), m_particleEffect(nullptr)
	{
		if (!p_pathToXML.empty())
		{
			m_particleEffect = new puppy::Effect(p_pathToXML.c_str());
		}
	}

	K_ParticleSystem::~K_ParticleSystem()
	{
		if (m_isEnabled)
		{
			onDisabled();
		}

		if (m_particleEffect != nullptr)
		{
			delete m_particleEffect;
		}
	}

	void K_ParticleSystem::start()
	{
		m_time = K_Time::getInstance();
		assert(m_time != nullptr);

		onEnabled();
	}

	void K_ParticleSystem::update()
	{
		if (m_particleEffect != nullptr)
		{
			m_particleEffect->update(m_time->getDeltaTime());
		}	
	}

	void K_ParticleSystem::onDisabled()
	{
		puppy::Renderer::sm_instance->removeParticleFromRender(this);
	}

	void K_ParticleSystem::onEnabled()
	{
		puppy::Renderer::sm_instance->addParticleToRender(this);
	}

	bool K_ParticleSystem::isPlaying() const
	{
		return m_isPlaying;
	}

	void K_ParticleSystem::setEffectXML(const std::string& p_pathToXML)
	{
		if (m_particleEffect != nullptr)
		{
			delete m_particleEffect;
		}

		m_particleEffect = new puppy::Effect(p_pathToXML.c_str());
	}

	void K_ParticleSystem::pause()
	{
		assert(m_particleEffect != nullptr);
		m_particleEffect->pause();
		m_isPlaying = false;
	}

	void K_ParticleSystem::play()
	{
		assert(m_particleEffect != nullptr);
		m_particleEffect->play();
		m_isPlaying = true;
	}

	void K_ParticleSystem::stop()
	{
		assert(m_particleEffect != nullptr);
		m_particleEffect->stop();
		m_isPlaying = false;
	}

	void K_ParticleSystem::refreshXML()
	{
		assert(m_particleEffect != nullptr);
		m_particleEffect->refreshXML();
	}

	void K_ParticleSystem::render(const glm::mat4& p_viewInverse, const glm::mat4& p_viewProj)
	{
		if (m_particleEffect != nullptr)
		{
			Transform& transform = getTransform();

			m_particleEffect->render(p_viewInverse, p_viewProj, transform.getTranslation(), transform.getScale());
		}	
	}
}