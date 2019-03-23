#include "DecreaseAmbientVolumeOnClick.h"

DecreaseAmbientVolumeOnClick::DecreaseAmbientVolumeOnClick(int p_amount) : m_amount(p_amount), m_controller(nullptr)
{
	m_enabledOnPause = true;
}

DecreaseAmbientVolumeOnClick::~DecreaseAmbientVolumeOnClick()
{

}

void DecreaseAmbientVolumeOnClick::start()
{
	ClickableUI::start();

	auto parent = getTransform().getParent();
	assert(parent != nullptr);

	m_controller = parent->getAttachedGameObject().getComponent<AmbientVolumeController>();
	assert(m_controller != nullptr);
}

void DecreaseAmbientVolumeOnClick::onClick()
{
	m_controller->changeAmbientVolume(-m_amount);
}