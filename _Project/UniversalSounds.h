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

	virtual void start() override;

	void privatePlaySound(const std::string& p_sound) const;
public:
	UniversalSounds(const std::list<std::pair<std::string, std::string>>& p_sounds);
	~UniversalSounds();

	static void playSound(const std::string& p_sound);
};