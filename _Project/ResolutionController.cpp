#include "ResolutionController.h"

#include "settings_menu\PlayerPrefs.h"

#include <Windows.h>
#include <iostream>

ResolutionController::ResolutionController()
{
	
}

ResolutionController::~ResolutionController()
{

}

void ResolutionController::start()
{
	// Setup possible resolutions
	RECT monitorRect;
	GetWindowRect(GetDesktopWindow(), &monitorRect);

	int monitorX = monitorRect.right;
	int monitorY = monitorRect.bottom;
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

std::pair<int, int> ResolutionController::getNextResolution()
{
	++m_currentRes;

	if (m_currentRes == m_resolutions.end())
	{
		m_currentRes = m_resolutions.begin();
	}

	return (*m_currentRes);
}

std::pair<int, int> ResolutionController::getPrevResolution()
{
	if (m_currentRes == m_resolutions.begin())
	{
		m_currentRes = m_resolutions.end();
	}

	--m_currentRes;

	return (*m_currentRes);
}
