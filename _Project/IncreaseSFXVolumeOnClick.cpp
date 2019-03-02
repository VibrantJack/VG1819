#include "IncreaseSFXVolumeOnClick.h"

#include "settings_menu\PlayerPrefs.h"

IncreaseSFXVolumeOnClick::IncreaseSFXVolumeOnClick(float p_amount) : m_amount(p_amount)
{

}

IncreaseSFXVolumeOnClick::~IncreaseSFXVolumeOnClick()
{

}

void IncreaseSFXVolumeOnClick::onClick()
{
	PlayerPrefs::setSFXVolume(m_amount + PlayerPrefs::getSFXVolume());
}