#include "PlaySoundOnStart.h"
#include "kitten\audio\AudioSource.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_ComponentManager.h"


PlaySoundOnStart::PlaySoundOnStart()
{

}

PlaySoundOnStart::~PlaySoundOnStart()
{

}

void PlaySoundOnStart::start()
{
	kitten::AudioSource* sound = m_attachedObject->getComponent<kitten::AudioSource>();
	assert(sound != nullptr);
	sound->play();

	kitten::K_ComponentManager::getInstance()->destroyComponent(this);
}