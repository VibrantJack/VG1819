#include "BGMVolumeController.h"
#include "util\MathUtil.h"
#include "settings_menu\PlayerPrefs.h"

BGMVolumeController::BGMVolumeController() : m_volume(0)
{

}

BGMVolumeController::~BGMVolumeController()
{

}

void BGMVolumeController::start()
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

	m_volume = PlayerPrefs::getBGMVolume();
	m_textBox->setText(std::to_string(m_volume) + "%");
}

void BGMVolumeController::changeBGMVolume(int p_amount)
{
	m_volume += p_amount;

	m_volume = CLAMP(m_volume, 0, 200);

	PlayerPrefs::setBGMVolume(m_volume);

	m_textBox->setText(std::to_string(m_volume) + "%");
}