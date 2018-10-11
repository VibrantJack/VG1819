#include "AudioSource.h"
#include "AudioEngineWrapper.h"
#include <iostream>

namespace kitten
{
	AudioSource::AudioSource(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects) : m_clipPath(p_pathToClip)
	{
		m_audioClip = AudioEngineWrapper::sm_instance->getSound(p_pathToClip, p_is3D, p_enableEffects);
		assert(m_audioClip != nullptr);
		
		m_is3D = p_is3D;
		m_effectsEnabled = p_enableEffects;
		setupMemberVars();
	}

	AudioSource::~AudioSource()
	{
		m_audioClip->stop();
		m_audioClip->drop();
		//m_audioClip->andRoll();
	}

	void AudioSource::start()
	{
		if (m_is3D)
		{
			Transform& transform = getTransform();
			const glm::vec3& vecPos = transform.getTranslation();
			transform.addPositionListener(this);

			onPosChanged(vecPos);
		}
	}

	void AudioSource::onPosChanged(const glm::vec3& p_newPos)
	{
		irrklang::vec3df pos(p_newPos.x, p_newPos.y, p_newPos.z);

		m_audioClip->setPosition(pos);
	}

	//Private helper
	void AudioSource::setupMemberVars() //Sets things that could be different from defaults because the audio source has custom defaults
	{
		m_clipLength = m_audioClip->getPlayLength();
		m_isLooped = m_audioClip->isLooped();
		m_volume = m_audioClip->getVolume();
		m_minDist = m_audioClip->getMinDistance();
		m_maxDist = m_audioClip->getMaxDistance();
	}

	void AudioSource::play()
	{
		if (m_audioClip->isFinished())
		{
			//remake audio source
			m_audioClip->stop(); // stop needed? 
			m_audioClip->drop();

			m_audioClip = AudioEngineWrapper::sm_instance->getSound(m_clipPath, m_is3D, m_effectsEnabled);
			m_audioClip->setVolume(m_volume);
			m_audioClip->setMinDistance(m_minDist);
			m_audioClip->setMaxDistance(m_maxDist);
			m_audioClip->setIsLooped(m_isLooped);
			m_audioClip->setIsPaused(false);
			onPosChanged(getTransform().getTranslation());
		}
		else
		{
			m_audioClip->setPlayPosition(0);
			m_audioClip->setIsPaused(false);
		}
	}

	void AudioSource::setClip(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects)
	{
		m_clipPath = p_pathToClip;

		m_audioClip = AudioEngineWrapper::sm_instance->getSound(p_pathToClip, p_is3D, p_enableEffects);
		assert(m_audioClip != nullptr);

		m_is3D = p_is3D;
		m_effectsEnabled = p_enableEffects;
		setupMemberVars();
	}

	void AudioSource::setPaused(bool p_paused)
	{
		m_audioClip->setIsPaused(p_paused);
	}

	bool AudioSource::isPaused() const
	{
		return m_audioClip->getIsPaused();
	}

	bool AudioSource::isFinished() const
	{
		return m_audioClip->isFinished();
	}

	void AudioSource::setLooped(bool p_looped)
	{
		m_audioClip->setIsLooped(p_looped);
		m_isLooped = p_looped;
	}

	bool AudioSource::isLooped()
	{
		return m_isLooped;
	}

	void AudioSource::setVolume(const float& p_volume)
	{
		m_audioClip->setVolume(p_volume);
		m_volume = p_volume;
	}

	float AudioSource::getVolume() const
	{
		return m_volume;
	}

	void AudioSource::setMinDistance(const float& p_dist)
	{
		m_audioClip->setMinDistance(p_dist);
		m_minDist = p_dist;
	}

	float AudioSource::getMinDistance() const
	{
		return m_minDist;
	}

	void AudioSource::setMaxDistance(const float& p_dist)
	{
		m_audioClip->setMaxDistance(p_dist);
		m_maxDist = p_dist;
	}

	float AudioSource::getMaxDistance() const
	{
		return m_maxDist;
	}

	void AudioSource::setPlayProgress(const float& p_place)
	{
		irrklang::ik_u32 toSet = m_clipLength / p_place;
		m_audioClip->setPlayPosition(toSet);
	}

	float AudioSource::getPlayProgress()
	{
		return m_audioClip->getPlayPosition() / m_clipLength;
	}
}