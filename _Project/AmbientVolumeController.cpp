#include "AmbientVolumeController.h"

#include "settings_menu\PlayerPrefs.h"

AmbientVolumeController::AmbientVolumeController() : m_textBox(nullptr), m_volume(100)
{

}

AmbientVolumeController::~AmbientVolumeController()
{

}

void AmbientVolumeController::start()
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

	m_volume = PlayerPrefs::getAmbientVolume();
	m_textBox->setText(std::to_string(m_volume) + "%");
}

void AmbientVolumeController::changeAmbientVolume(int p_amount)
{
	m_volume += p_amount;

	m_volume = CLAMP(m_volume, 0, 200);

	PlayerPrefs::setAmbientVolume(m_volume);

	m_textBox->setText(std::to_string(m_volume) + "%");
}