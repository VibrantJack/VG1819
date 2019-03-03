#pragma once

#include "kitten\K_Component.h"

#include <list>
#include <tuple>

class ResolutionController : public kitten::K_Component
{
private:
	std::list<std::pair<int, int>> m_resolutions;
	std::list<std::pair<int, int>>::iterator m_currentRes;

	virtual void start() override;
public:
	ResolutionController();
	~ResolutionController();

	void setResolution(int p_windowX, int p_windowY);

	std::pair<int, int> getNextResolution();
	std::pair<int, int> getPrevResolution();
};