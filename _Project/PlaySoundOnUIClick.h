#pragma once

#include "kitten\audio\AudioSource.h"
#include "kitten\mouse picking\ClickableUI.h"

class PlaySoundOnUIClick : public kitten::ClickableUI
{
private:
	kitten::AudioSource* m_audioSource;

	virtual void start() override;
	virtual void onClick() override;
public:
	PlaySoundOnUIClick();
	~PlaySoundOnUIClick();
};