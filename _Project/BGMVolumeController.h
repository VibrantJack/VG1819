#pragma once

#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"

// I really should have just made an options_menu controller - Callum
class BGMVolumeController : public kitten::K_Component
{
private:
	int m_volume;
	puppy::TextBox* m_textBox;

	virtual void start() override;
public:
	BGMVolumeController();
	~BGMVolumeController();

	void changeBGMVolume(int p_amount);
	int getCurrentBGMVolume() const { return m_volume; };
};