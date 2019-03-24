#pragma once

#include "kitten\K_Component.h"
#include "kitten\audio\AudioSource.h"

#include <string>
#include <unordered_map>

// Pretty much universal sounds but plays one sound at a time -Callum

class BGMManager : public kitten::K_Component
{
private:
	struct BGMEntry
	{
		kitten::AudioSource* source;
		const float originalVolume;

		BGMEntry(kitten::AudioSource* s, const float& v)
			: source(s), originalVolume(v) {};
	};

	static BGMManager* sm_instance;

	std::list<std::pair<std::string, std::string>> m_soundsToCreate;
	
	kitten::AudioSource* m_playingSource;
	std::string m_playingName;
	std::unordered_map<std::string, BGMEntry> m_tracks;

	float m_volume;
	float m_crossFadeTime;

	virtual void start() override;

	void privatePlayBGM(const std::string& p_name);
	void privateStopBGM();

	void privateSetVolume(float p_volume);
public:
	BGMManager(const std::list<std::pair<std::string, std::string>>& p_sounds, float p_crossFadeTime);
	~BGMManager();

	static void playBGM(const std::string& p_name);
	static void stopBGM();

	static void setVolume(float p_volume);
};