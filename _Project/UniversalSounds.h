#pragma once

#include "kitten\K_Component.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\audio\AudioSource.h"

#include <list>
#include <string>
#include <unordered_map>

class UniversalSounds : public kitten::K_Component
{
private:
	static UniversalSounds* sm_instance;

	std::unordered_map<std::string, kitten::AudioSource*> m_sounds;
	std::list<std::pair<std::string, std::string>> m_soundsToCreate;

	float m_volume;

	virtual void start() override;

	void privatePlaySound(const std::string& p_sound) const;
	void privateSetVolume(float p_volume);
public:
	UniversalSounds(const std::list<std::pair<std::string, std::string>>& p_sounds);
	~UniversalSounds();

	static void playSound(const std::string& p_sound);

	// Modify the volume from 0.0 - 1.0
	static void setVolume(float p_volume);

	static float getVolume();
};