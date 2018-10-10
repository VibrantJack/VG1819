#include "AudioEngineWrapper.h"
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

	AudioEngineWrapper::AudioEngineWrapper()
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
		auto found = m_createdSources.find(p_pathToClip);
		if (found != m_createdSources.end())
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
		m_createdSources.insert(std::make_pair(p_pathToClip, source));

		if (p_is3D)
		{
			return m_audioEngine->play3D(source, irrklang::vec3df(0, 0, 0), false, true, false, p_enableEffects);
		}
		else
		{
			return m_audioEngine->play2D(source, false, true, false, p_enableEffects);
		}
	}
}