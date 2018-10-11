#pragma once
#include <string>

#include "AudioEngineWrapper.h"
#include "kitten\K_Component.h"
#include "kitten\Transform.h"

namespace kitten
{
	class AudioSource : public K_Component, public TransformPositionListener
	{
	private:
		irrklang::ISound* m_audioClip;

		std::string m_clipPath; //Mostly for debugging

		irrklang::ik_u32 m_clipLength;
		bool m_isLooped;
		bool m_is3D;
		bool m_effectsEnabled;

		float m_volume;
		float m_minDist, m_maxDist;

		void setupMemberVars();
	public:
		AudioSource(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects);
		~AudioSource();

		void start() override;
		void onPosChanged(const glm::vec3& p_newPos) override;

		void play();

		void setClip(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects);
		
		void setPaused(bool p_paused);
		bool isPaused() const;
		bool isFinished() const;

		void setLooped(bool p_looped);
		bool isLooped();

		void setVolume(const float& p_volume); //Between 0 and 1
		float getVolume() const;

		void setMinDistance(const float& p_dist); //3D distance you have to be from source to hear the sound
		float getMinDistance() const;

		void setMaxDistance(const float& p_dist);
		float getMaxDistance() const;

		// irrKlang normally uses unsigned int of milliseconds for these
		// could add if 0-1 value is not useful -Callum
		void setPlayProgress(const float& p_place);
		float getPlayProgress(); // Returns between 0 and 1, 0 = none, 1 = done
		
		// Effects

	};
}