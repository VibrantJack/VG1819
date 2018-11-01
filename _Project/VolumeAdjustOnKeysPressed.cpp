#include "VolumeAdjustOnKeysPressed.h"
#include "kitten\K_GameObject.h"
#include "util\MathUtil.h"

VolumeAdjustOnKeysPressed::VolumeAdjustOnKeysPressed(char p_increaseKey, char p_decreaseKey, float p_changeAmount) : m_increaseKey(p_increaseKey), m_decreaseKey(p_decreaseKey),
	m_changeAmount(p_changeAmount)
{

}

VolumeAdjustOnKeysPressed::~VolumeAdjustOnKeysPressed()
{

}

void VolumeAdjustOnKeysPressed::start()
{
	m_audioSource = m_attachedObject->getComponent<kitten::AudioSource>();
	m_inputMan = input::InputManager::getInstance();

	assert(m_audioSource != nullptr && m_inputMan != nullptr);
}

void VolumeAdjustOnKeysPressed::update()
{
	//Decrease volume
	if (m_inputMan->keyDown(m_decreaseKey) && !m_inputMan->keyDownLast(m_decreaseKey))
	{
		m_audioSource->setVolume(CLAMP(m_audioSource->getVolume() - m_changeAmount,0.0f,1.0f));
	}
	else if (m_inputMan->keyDown(m_increaseKey) && !m_inputMan->keyDownLast(m_increaseKey))
	{
		//Increase volume
		m_audioSource->setVolume(CLAMP(m_audioSource->getVolume() + m_changeAmount, 0.0f, 1.0f));
	}
}