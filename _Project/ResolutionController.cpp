#include "ResolutionController.h"

#include "settings_menu\PlayerPrefs.h"

#include <Windows.h>
#include <iostream>

#define WINDOW_ASPECT_RATIO (1080.0f/1920.0f)

ResolutionController::ResolutionController() : m_textBox(nullptr)
{
	
}

ResolutionController::~ResolutionController()
{

}

void ResolutionController::start()
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

	// Setup possible resolutions
	RECT monitorRect;
	GetWindowRect(GetDesktopWindow(), &monitorRect);

	int monitorX = monitorRect.right;
	int monitorY = monitorRect.bottom;

	//Create resolutions based on aspect ratio, windowX decreasing by at least 100 ? idk
	int currentX = monitorX;

	while (currentX > 300)
	{
		float nextY = currentX * WINDOW_ASPECT_RATIO;
		if ((float)(nextY - (int)nextY) == 0.0f)
		{
			//Insert into list
			m_resolutions.push_front(std::make_pair(currentX, nextY));
		}

		currentX -= 100;
	}

	// Set iterator to current window resolution
	int windowX = input::InputManager::getInstance()->getWindowWidth();
	int windowY = input::InputManager::getInstance()->getWindowHeight();

	//Search for resolution in list
	std::pair<int, int> res(windowX, windowY);
	bool found = false;

	auto end = m_resolutions.cend();
	for (auto it = m_resolutions.begin(); it != end; ++it)
	{
		if ((*it) == res)
		{
			m_currentRes = it;
			found = true;
			break;
		}
	}

	if (!found)
	{
		// Set res to maximum and save
		m_currentRes = --m_resolutions.end();

		applyRes();

		PlayerPrefs::saveAllSettings();
	}
	else
	{
		m_textBox->setText(std::to_string(windowX) + " x " + std::to_string(windowY));
	}
}

void ResolutionController::setResolution(int p_windowX, int p_windowY)
{
	std::pair<int, int> res(p_windowX, p_windowY);
	
	//Search for resolution in list
	auto end = m_resolutions.cend();
	for (auto it = m_resolutions.begin(); it != end; ++it)
	{
		if ((*it) == res)
		{
			m_currentRes = it;
			PlayerPrefs::setResolution(p_windowX, p_windowY);
			return;
		}
	}
}

void ResolutionController::nextRes()
{
	++m_currentRes;

	if (m_currentRes == m_resolutions.end())
	{
		m_currentRes = m_resolutions.begin();
	}

	applyRes();
}

void ResolutionController::prevRes()
{
	if (m_currentRes == m_resolutions.begin())
	{
		m_currentRes = m_resolutions.end();
	}

	--m_currentRes;

	applyRes();
}

void ResolutionController::applyRes()
{
	auto resPair = *m_currentRes;
	PlayerPrefs::setResolution(resPair.first, resPair.second);

	m_textBox->setText(std::to_string(resPair.first) + " x " + std::to_string(resPair.second));
}
