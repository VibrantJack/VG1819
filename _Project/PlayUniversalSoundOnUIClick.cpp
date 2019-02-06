#include "PlayUniversalSoundOnUIClick.h"

PlayUniversalSoundOnUIClick::PlayUniversalSoundOnUIClick(const std::string& p_soundName) : m_soundName(p_soundName)
{
	m_enabledOnPause = true;
}

PlayUniversalSoundOnUIClick::~PlayUniversalSoundOnUIClick()
{

}

void PlayUniversalSoundOnUIClick::onClick()
{
	UniversalSounds::playSound(m_soundName);
}