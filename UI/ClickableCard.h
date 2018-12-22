#pragma once
#include "kitten\mouse picking\ClickableUI.h"
#include "kitten\K_GameObject.h"
#include "puppy\Text\FontTable.h"
#include "puppy\Text\Font.h"
#include "puppy\Text\TextBox.h"
#include "puppy\Text\TextTable.h"


namespace userinterface
{
	class ContextMenu;

	class ClickableCard : public kitten::ClickableUI, public kitten::TransformPositionListener
	{
	protected:
		ContextMenu* m_currentContext;
		bool m_enabledOnPause;
	public:
		ClickableCard(bool p_enabledOnPause = false);
		~ClickableCard();

		void onHoverStart() override;
		void onHoverEnd() override;
		void onPause() override;
		void onPosChanged(const glm::vec3& p_newPos) override;

		kitten::K_GameObject* m_context;
		void setEnabledOnPause(bool p_enable) { m_enabledOnPause = p_enable; }
		bool isEnabledOnPause() { return m_enabledOnPause; }
	};
}
