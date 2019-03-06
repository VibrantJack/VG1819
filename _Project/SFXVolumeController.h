#pragma once

#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"

class SFXVolumeController : public kitten::K_Component
{
private:
	int m_volume;
	puppy::TextBox* m_textBox;

	virtual void start() override;
public:
	SFXVolumeController();
	~SFXVolumeController();

	void changeSFXVolume(int p_amount);

	float getCurrentSFXVolume() const { return m_volume; };
};