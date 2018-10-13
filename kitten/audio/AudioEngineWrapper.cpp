#include "AudioEngineWrapper.h"
#include "AudioSource.h"
#include <assert.h>
#include <iostream>

namespace kitten
{
	AudioEngineWrapper* AudioEngineWrapper::sm_instance = nullptr;

	void AudioEngineWrapper::createInstance()
	{
		assert(sm_instance == nullptr);
		sm_instance = new AudioEngineWrapper();
	}

	void AudioEngineWrapper::destroyInstance()
	{
		assert(sm_instance != nullptr);
		delete sm_instance;
	}

	AudioEngineWrapper::AudioEngineWrapper() : m_lowestDuck(1.0f)
	{
		m_audioEngine = irrklang::createIrrKlangDevice();
		std::cout << "MultiThreaded audio? " << (m_audioEngine->isMultiThreaded() ? "Yes" : "No") << std::endl;
		assert(m_audioEngine != nullptr);
	}

	AudioEngineWrapper::~AudioEngineWrapper()
	{
		m_audioEngine->drop();
	}

	void AudioEngineWrapper::update()
	{
		sm_instance->m_audioEngine->update();
	}

	irrklang::ISound* AudioEngineWrapper::getSound(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects)
	{
		auto found = m_createdSoundSources.find(p_pathToClip);
		if (found != m_createdSoundSources.end())
		{
			if (p_is3D)
			{
				return m_audioEngine->play3D(found->second, irrklang::vec3df(0, 0, 0), false, true, false, p_enableEffects);
			}
			else
			{
				return m_audioEngine->play2D(found->second, false, true, false, p_enableEffects);
			}
		}

		// Have to create a sound source for this clip
		irrklang::ISoundSource* source = m_audioEngine->addSoundSourceFromFile(p_pathToClip.c_str());
		m_createdSoundSources.insert(std::make_pair(p_pathToClip, source));

		if (p_is3D)
		{
			return m_audioEngine->play3D(source, irrklang::vec3df(0, 0, 0), false, true, false, p_enableEffects);
		}
		else
		{
			return m_audioEngine->play2D(source, false, true, false, p_enableEffects);
		}
	}

	void AudioEngineWrapper::addToDuck(AudioSource* p_toDuck)
	{
		m_sourcesToDuck.insert(p_toDuck);

		//See if we should start ducking this right away
		if (!m_duckingSources.empty())
		{
			p_toDuck->startDucking(m_lowestDuck);
		}
	}

	void AudioEngineWrapper::removeFromDuck(AudioSource* p_toRemove)
	{
		m_sourcesToDuck.erase(p_toRemove);
	}

	void AudioEngineWrapper::startDuck(float p_factor)
	{
		//Add duck entry
		m_duckingSources.insert(p_factor);

		//Check if this is a lower duck than the previous duck
		if (p_factor < m_lowestDuck)
		{
			m_lowestDuck = p_factor;
			//Lower ducked sources
			duckSources();
		}
	}

	void AudioEngineWrapper::stopDuck(float p_factor)
	{
		//Remove duck entry
		m_duckingSources.erase(p_factor);

		if (m_duckingSources.empty())
		{
			//stop ducking
			stopDucking();
			return;
		}
		//else

		//Check if that was the lowest duck
		if (p_factor == m_lowestDuck)
		{
			//Check if there was a duplicate entry with the same factor
			if (m_duckingSources.find(p_factor) != m_duckingSources.end())
			{
				//the lowest duck is the same as before, no action required
				return;
			}
			//else

			//We need to update the ducked sources with the new factor
			m_lowestDuck = *(m_duckingSources.rbegin());
			duckSources();
		}
	}

	void AudioEngineWrapper::duckSources()
	{
		auto end = m_sourcesToDuck.cend();
		for (auto it = m_sourcesToDuck.cbegin(); it != end; ++it)
		{
			(*it)->startDucking(m_lowestDuck);
		}
	}

	void AudioEngineWrapper::stopDucking()
	{
		m_lowestDuck = 1.0f;
		auto end = m_sourcesToDuck.cend();
		for (auto it = m_sourcesToDuck.cbegin(); it != end; ++it)
		{
			(*it)->stopDucking();
		}
	}
}