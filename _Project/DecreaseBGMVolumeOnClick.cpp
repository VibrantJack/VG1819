#include "DecreaseBGMVolumeOnClick.h"

DecreaseBGMVolumeOnClick::DecreaseBGMVolumeOnClick(int p_amount) : m_amount(p_amount), m_controller(nullptr)
{

}

DecreaseBGMVolumeOnClick::~DecreaseBGMVolumeOnClick()
{

}

void DecreaseBGMVolumeOnClick::start()
{
	ClickableUI::start();

	auto parent = getTransform().getParent();
	assert(parent != nullptr);

	m_controller = parent->getAttachedGameObject().getComponent<BGMVolumeController>();
	assert(m_controller != nullptr);
}

void DecreaseBGMVolumeOnClick::onClick()
{
	m_controller->changeBGMVolume(-m_amount);
}