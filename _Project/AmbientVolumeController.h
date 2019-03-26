#pragma once
#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"

// I really should have just made an options_menu controller - Callum
class AmbientVolumeController : public kitten::K_Component
{
private:
	int m_volume;
	puppy::TextBox* m_textBox;

	virtual void start();
public:
	AmbientVolumeController();
	~AmbientVolumeController();

	void changeAmbientVolume(int p_amount);
	int getCurrentAmbientVolume() const { return m_volume; }
};