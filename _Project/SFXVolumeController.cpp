#include "SFXVolumeController.h"
#include "util\MathUtil.h"
#include "settings_menu\PlayerPrefs.h"

SFXVolumeController::SFXVolumeController() : m_volume(0)
{

}

SFXVolumeController::~SFXVolumeController()
{

}

void SFXVolumeController::start()
{
	auto children = getTransform().getChildren();
	assert(!children.empty());

	auto childrenEnd = children.cend();
	for (auto it = children.begin(); it != childrenEnd; ++it)
	{
		m_textBox = (*it)->getAttachedGameObject().getComponent<puppy::TextBox>();
		if (m_textBox != nullptr)
		{
			break;
		}
	}

	assert(m_textBox != nullptr);

	m_volume = PlayerPrefs::getSFXVolume();
	m_textBox->setText(std::to_string(m_volume) + "%");
}

void SFXVolumeController::changeSFXVolume(int p_amount)
{
	m_volume += p_amount;

	m_volume = CLAMP(m_volume, 0, 200);

	PlayerPrefs::setSFXVolume(m_volume);

	m_textBox->setText(std::to_string(m_volume) + "%");
}