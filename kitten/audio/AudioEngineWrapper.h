#pragma once
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include <string>
#include <unordered_map>
#include <set>

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

		std::unordered_map<std::string, irrklang::ISoundSource*> m_createdSoundSources;

		std::set<AudioSource*> m_sourcesToDuck;
		std::multiset<int> m_duckingSources; // The factors that are causing a duck. Only the lowest is applied
		float m_lowestDuck;

		// Methods to help AudioSource
		irrklang::ISound* getSound(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects);
		//Duck related
		void addToDuck(AudioSource* p_toDuck);
		void removeFromDuck(AudioSource* p_toRemove);

		void startDuck(float p_factor);
		void stopDuck(float p_factor);
		
		//Helper for AudioEngineWrapper
		void duckSources();
		void stopDucking();
	public:
		
		//Public static
		static void createInstance();
		static void destroyInstance();

		static void update();
	};
}