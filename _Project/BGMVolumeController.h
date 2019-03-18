#pragma once

#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"

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

	float getCurrentBGMVolume() const { return m_volume; };
};