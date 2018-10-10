#pragma once
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include <string>
#include <unordered_map>

namespace kitten
{
	class AudioSource;
	class AudioListener;

	class AudioEngineWrapper
	{
		friend class AudioSource;
		friend class AudioListener;
	private:
		AudioEngineWrapper();
		~AudioEngineWrapper();

		static AudioEngineWrapper* sm_instance;
		irrklang::ISoundEngine* m_audioEngine;

		std::unordered_map<std::string, irrklang::ISoundSource*> m_createdSources;

		// Methods to help AudioSource
		irrklang::ISound* getSound(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects);
	public:
		static void createInstance();
		static void destroyInstance();

		static void update();

	};
}