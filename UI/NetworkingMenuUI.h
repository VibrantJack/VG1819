#pragma once

#include "UIFrame.h"

namespace userinterface
{
	//class NetworkingMenuUI;

	class NetworkingMenuUI : public UIFrame
	{
	public:
		NetworkingMenuUI(const char* p_pathToTex);
		~NetworkingMenuUI();

		void init();

	private:

	};
}