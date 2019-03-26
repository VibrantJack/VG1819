#include "PlayUniversalSoundOnEnable.h"

#include "_Project\UniversalSounds.h"

PlayUniversalSoundOnEnable::PlayUniversalSoundOnEnable(const std::string& p_soundName, bool p_is3D) : m_soundName(p_soundName), m_is3D(p_is3D)
{

}

PlayUniversalSoundOnEnable::~PlayUniversalSoundOnEnable()
{

}

void PlayUniversalSoundOnEnable::onEnabled()
{
	if (m_is3D)
	{
		UniversalSounds::playSound(m_soundName, getTransform().getTranslation());
	}
	else
	{
		UniversalSounds::playSound(m_soundName);
	}
	
}