#pragma once

#include "UIObject.h"
#include "puppy\Text\TextBox.h"
#include "unit\Unit.h"

//austin's UI Object

namespace userinterface
{
	class HandFrame;

	class CardUIO : public UIObject
	{
	private:
		HandFrame* m_parentHand;
		puppy::TextBox* m_unitNameTextBox;
		UIObject* m_unitPortrait;
		unit::Unit* m_unit;
	public:
		CardUIO(const char* p_pathToTex);
		~CardUIO();

		virtual void start() override;

		void returnToHand();
		void scaleAsCard();
		void assignParentHand(HandFrame* p_toAssign);

		void setUnit(unit::Unit* p_unit);
		unit::Unit* getUnit() { return m_unit; }

	};
		
}