#pragma once

#include "kitten\mouse picking\Clickable.h"
#include "kitten\audio\AudioSource.h"

class PlaySoundOnClick : public kitten::Clickable
{
private:
	const std::string m_soundName;
	const bool m_is3D;

	virtual void onClick() override;

public:
	PlaySoundOnClick(const std::string& p_soundName, bool p_is3D);
	~PlaySoundOnClick();
};