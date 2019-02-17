#include "PlayUniversalSoundOnEnable.h"

#include "_Project\UniversalSounds.h"

PlayUniversalSoundOnEnable::PlayUniversalSoundOnEnable(const std::string& p_soundName) : m_soundName(p_soundName)
{

}

PlayUniversalSoundOnEnable::~PlayUniversalSoundOnEnable()
{

}

void PlayUniversalSoundOnEnable::onEnabled()
{
	UniversalSounds::playSound(m_soundName);
}