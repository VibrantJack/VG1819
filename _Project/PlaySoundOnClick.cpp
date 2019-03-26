#include "PlaySoundOnClick.h"
#include "UniversalSounds.h"

PlaySoundOnClick::PlaySoundOnClick(const std::string& p_soundName, bool p_is3D) : m_soundName(p_soundName), m_is3D(p_is3D)
{

}

PlaySoundOnClick::~PlaySoundOnClick()
{

}


void PlaySoundOnClick::onClick()
{
	if (!m_is3D)
	{
		UniversalSounds::playSound(m_soundName);
	}
	else
	{
		UniversalSounds::playSound(m_soundName, getTransform().getTranslation());
	}
}