#include "AudioSource.h"
#include "AudioEngineWrapper.h"
#include "util\MathUtil.h"
#include <iostream>

namespace kitten
{
	AudioSource::AudioSource(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects, bool p_causesDuck, bool p_getsDucked) : m_clipPath(p_pathToClip),
		m_is3D(p_is3D),  m_effectsEnabled(p_enableEffects), m_causesDuck(p_causesDuck), m_beingDucked(false), m_getsDucked(p_getsDucked)
	{
		m_audioClip = AudioEngineWrapper::sm_instance->getSound(p_pathToClip, p_is3D, p_enableEffects);
		assert(m_audioClip != nullptr);
		
		m_sfxController = new SoundEffectsApplier(m_audioClip->getSoundEffectControl());

		setupMemberVars();

		if (p_getsDucked)
		{
			AudioEngineWrapper::sm_instance->addToDuck(this);
		}
	}

	AudioSource::~AudioSource()
	{
		m_audioClip->stop();
		m_audioClip->drop();
		//m_audioClip->andRoll();

		if (m_getsDucked)
		{
			AudioEngineWrapper::sm_instance->removeFromDuck(this);
		}

		delete m_sfxController;
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
		m_causingDuckFactor = (m_volume / 1.0f) - 0.75f;

		if (m_causesDuck)
		{
			m_audioClip->setSoundStopEventReceiver(this);
		}
	}

	void AudioSource::play()
	{	
		if (m_audioClip->isFinished())
		{
			//remake audio source
			m_audioClip->stop(); // stop needed? 
			m_audioClip->drop();

			m_audioClip = AudioEngineWrapper::sm_instance->getSound(m_clipPath, m_is3D, m_effectsEnabled);
			m_audioClip->setMinDistance(m_minDist);
			m_audioClip->setMaxDistance(m_maxDist);
			m_audioClip->setIsLooped(m_isLooped);
			m_audioClip->setIsPaused(false);
			m_sfxController->setController(m_audioClip->getSoundEffectControl());
			m_sfxController->applyEffects();

			if (m_is3D)
			{
				onPosChanged(getTransform().getTranslation());
			}

			if (m_beingDucked)
			{
				m_audioClip->setVolume(m_volume * m_beingDuckedFactor);
			}
			else
			{
				m_audioClip->setVolume(m_volume);
			}
			if (m_causesDuck)
			{
				m_audioClip->setSoundStopEventReceiver(this);
			}
		}
		else
		{
			m_audioClip->setPlayPosition(0);
			m_audioClip->setIsPaused(false);
		}

		if (m_causesDuck)
		{
			tryDuckOthers(true);
		}
	}

	void AudioSource::setClip(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects)
	{
		if (m_causesDuck)
		{
			tryDuckOthers(false);
		}

		m_audioClip->stop();
		m_audioClip->drop();
		
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
		
		if (m_causesDuck)
		{
			tryDuckOthers(!p_paused);
		}
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
		m_volume = p_volume;
		m_causingDuckFactor = (m_volume / 1.0f) - 0.75f;

		if (m_beingDucked)
		{
			m_audioClip->setVolume(p_volume * m_beingDuckedFactor);
		}
		else
		{
			m_audioClip->setVolume(p_volume);
		}

		if (m_causesDuck)
		{
			tryDuckOthers(true);
		}
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

	SoundEffectsApplier* AudioSource::getSFXControl()
	{
		return m_sfxController;
	}

	void AudioSource::startDucking(const float& p_factor)
	{
		m_beingDucked = true;
		m_beingDuckedFactor = p_factor;
		m_audioClip->setVolume(m_volume * p_factor);
	}

	void AudioSource::stopDucking()
	{
		m_beingDucked = false;
		m_audioClip->setVolume(m_volume);
	}

	void AudioSource::tryDuckOthers(bool p_startDuck)
	{
		if (p_startDuck)
		{
			if (!m_audioClip->getIsPaused()) //Does this work if the audioClip is finished as well?
			{
				AudioEngineWrapper::sm_instance->startDuck(m_causingDuckFactor);
			}
		}
		else
		{
			if (m_audioClip->getIsPaused() || m_audioClip->isFinished())
			{
				AudioEngineWrapper::sm_instance->stopDuck(m_causingDuckFactor);
			}
		}
	}

	void AudioSource::OnSoundStopped(irrklang::ISound* p_sound, irrklang::E_STOP_EVENT_CAUSE p_reason, void* p_userData)
	{
		if (m_causesDuck)
		{
			tryDuckOthers(false);
		}
	}
}