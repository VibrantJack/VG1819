#pragma once
#include "kitten\mouse picking\ClickableUI.h"
#include "UniversalSounds.h"

#include <string>

class PlayUniversalSoundOnUIClick : public kitten::ClickableUI
{
private:
	const std::string m_soundName;

	virtual void onClick() override;
public:
	PlayUniversalSoundOnUIClick(const std::string& p_soundName);
	~PlayUniversalSoundOnUIClick();
};