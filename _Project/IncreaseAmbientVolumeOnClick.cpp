#include "IncreaseAmbientVolumeOnClick.h"

IncreaseAmbientVolumeOnClick::IncreaseAmbientVolumeOnClick(int p_amount) : m_amount(p_amount), m_controller(nullptr)
{
	m_enabledOnPause = true;
}

IncreaseAmbientVolumeOnClick::~IncreaseAmbientVolumeOnClick()
{

}

void IncreaseAmbientVolumeOnClick::start()
{
	ClickableUI::start();

	auto parent = getTransform().getParent();
	assert(parent != nullptr);

	m_controller = parent->getAttachedGameObject().getComponent<AmbientVolumeController>();
	assert(m_controller != nullptr);
}

void IncreaseAmbientVolumeOnClick::onClick()
{
	m_controller->changeAmbientVolume(m_amount);
}