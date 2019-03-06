#include "IncreaseBGMVolumeOnClick.h"

IncreaseBGMVolumeOnClick::IncreaseBGMVolumeOnClick(int p_amount) : m_amount(p_amount), m_controller(nullptr)
{

}

IncreaseBGMVolumeOnClick::~IncreaseBGMVolumeOnClick()
{

}

void IncreaseBGMVolumeOnClick::start()
{
	ClickableUI::start();

	auto parent = getTransform().getParent();
	assert(parent != nullptr);

	m_controller = parent->getAttachedGameObject().getComponent<BGMVolumeController>();
	assert(m_controller != nullptr);
}

void IncreaseBGMVolumeOnClick::onClick()
{
	m_controller->changeBGMVolume(m_amount);
}