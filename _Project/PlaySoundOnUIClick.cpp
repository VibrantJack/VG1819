#include "PlaySoundOnUIClick.h"

PlaySoundOnUIClick::PlaySoundOnUIClick()
{

}

PlaySoundOnUIClick::~PlaySoundOnUIClick()
{

}

void PlaySoundOnUIClick::start()
{
	ClickableUI::start();

	m_audioSource = m_attachedObject->getComponent<kitten::AudioSource>();
	assert(m_audioSource != nullptr);
}

void PlaySoundOnUIClick::onClick()
{
	m_audioSource->play();
}