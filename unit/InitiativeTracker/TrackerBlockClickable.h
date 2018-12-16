#pragma once

#include <string>
#include "kitten/mouse picking/ClickableUI.h"
#include "kitten/mouse picking/Clickable.h"

namespace unit
{
	class TrackerBlockClickable : public kitten::Clickable
	{
	private:
		kitten::K_GameObject* m_txtGO;

	public:
		TrackerBlockClickable();
		virtual ~TrackerBlockClickable();

		virtual void onClick() override;
		virtual void onHoverStart() override;
		virtual void onHoverEnd() override;

		void setTextBox(kitten::K_GameObject* p_txt);
	};
}