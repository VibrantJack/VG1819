#include "DecreaseSFXVolumeOnClick.h"

#include "_Project\UniversalSounds.h"

DecreaseSFXVolumeOnClick::DecreaseSFXVolumeOnClick(int p_amount) : m_amount(p_amount), m_controller(nullptr)
{

}

DecreaseSFXVolumeOnClick::~DecreaseSFXVolumeOnClick()
{

}

void DecreaseSFXVolumeOnClick::start()
{
	ClickableUI::start();

	auto parent = getTransform().getParent();
	assert(parent != nullptr);

	m_controller = parent->getAttachedGameObject().getComponent<SFXVolumeController>();
	assert(m_controller != nullptr);
}

void DecreaseSFXVolumeOnClick::onClick()
{
	m_controller->changeSFXVolume(-m_amount);
}