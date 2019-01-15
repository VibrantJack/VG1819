#pragma once

#include <string>
#include "kitten/mouse picking/ClickableUI.h"
#include "kitten/mouse picking/Clickable.h"
#include "UI/CardContext.h"

namespace unit
{
	class TrackerBlockClickable : public kitten::ClickableUI
	{
	private:
		kitten::K_GameObject* m_txtGO;
		kitten::K_GameObject* m_unit;

	public:
		TrackerBlockClickable();
		virtual ~TrackerBlockClickable();

		virtual void onClick() override;
		virtual void onHoverStart() override;
		virtual void onHoverEnd() override;
		virtual void onPause();

		void setTextBox(kitten::K_GameObject* p_txt);
		void setUnit(kitten::K_GameObject* p_unit);
	};
}