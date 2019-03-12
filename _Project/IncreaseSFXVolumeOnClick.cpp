#include "IncreaseSFXVolumeOnClick.h"

#include "settings_menu\PlayerPrefs.h"

IncreaseSFXVolumeOnClick::IncreaseSFXVolumeOnClick(int p_amount) : m_amount(p_amount), m_controller(nullptr)
{
	m_enabledOnPause = true;
}

IncreaseSFXVolumeOnClick::~IncreaseSFXVolumeOnClick()
{

}

void IncreaseSFXVolumeOnClick::start()
{
	ClickableUI::start();

	auto parent = getTransform().getParent();
	assert(parent != nullptr);

	m_controller = parent->getAttachedGameObject().getComponent<SFXVolumeController>();
	assert(m_controller != nullptr);
}

void IncreaseSFXVolumeOnClick::onClick()
{
	m_controller->changeSFXVolume(m_amount);
}