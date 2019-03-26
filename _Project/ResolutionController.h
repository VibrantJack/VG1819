#pragma once

#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"

#include <list>
#include <tuple>

// I really should have just made an options_menu controller - Callum
class ResolutionController : public kitten::K_Component
{
private:
	
	std::list<std::pair<int, int>> m_resolutions;
	std::list<std::pair<int, int>>::iterator m_currentRes;
	puppy::TextBox* m_textBox;

	virtual void start() override;

	void applyRes();
public:
	ResolutionController();
	~ResolutionController();

	void nextRes();
	void prevRes();
	void setResolution(int p_windowX, int p_windowY);
};