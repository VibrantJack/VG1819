#include "DecreaseSFXVolumeOnClick.h"

#include "_Project\UniversalSounds.h"

DecreaseSFXVolumeOnClick::DecreaseSFXVolumeOnClick(float p_amount) : m_amount(p_amount)
{

}

DecreaseSFXVolumeOnClick::~DecreaseSFXVolumeOnClick()
{

}

void DecreaseSFXVolumeOnClick::onClick()
{
	UniversalSounds::setVolume(UniversalSounds::getVolume() - m_amount);
}