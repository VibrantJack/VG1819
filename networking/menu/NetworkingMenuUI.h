#pragma once

#include "UI/UIFrame.h"
#include "networking\NetworkingConsoleMenu.h"

namespace userinterface
{
	class ClickableUI;

	class NetworkingMenuUI : public UIFrame
	{
		friend class NetworkHostButton;
	public:
		NetworkingMenuUI(const char* p_pathToTex);
		~NetworkingMenuUI();

		virtual void start() override;
		//void init();
		void addButton(ClickableUI* p_button);

	private:
		NetworkingConsoleMenu* m_menu;


	};
}