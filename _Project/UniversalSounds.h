#pragma once

#include "kitten\K_Component.h"
#include "kitten\audio\AudioSource.h"

#include <list>
#include <string>
#include <unordered_map>

class UniversalSounds : public kitten::K_Component
{
private:
	struct SoundEntry
	{
		kitten::AudioSource* source;
		const float originalVolume;

		SoundEntry(kitten::AudioSource* s, const float& v)
			: source(s), originalVolume(v) {};
	};
	
	static UniversalSounds* sm_instance;

	std::unordered_map<std::string, SoundEntry> m_sounds;
	std::list<std::pair<std::string, std::string>> m_soundsToCreate;

	float m_volume;

	virtual void start() override;

	void privatePlaySound(const std::string& p_sound) const;
	void privatePlaySound(const std::string& p_sound, const glm::vec3& p_place) const;
	void privateSetVolume(float p_volume);

	

public:
	UniversalSounds(const std::list<std::pair<std::string, std::string>>& p_sounds);
	~UniversalSounds();

	static void playSound(const std::string& p_sound);
	static void playSound(const std::string& p_sound, const glm::vec3& p_place);

	// Modify the volume from 0.0 - 1.0
	static void setVolume(float p_volume);

	static float getVolume();
};