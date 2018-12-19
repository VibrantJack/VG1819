#pragma once

#include <string>
#include "kitten/mouse picking/Clickable.h"
#include "kitten\event_system\EventManager.h"
#include "puppy\Text\TextBox.h"

class SendSelfOnClick : public kitten::Clickable
{
private:
	puppy::TextBox* m_tileInfoDisplay;

	void setTileInfoDisplayText();
	void getPadding(const std::string& p_string, std::string& p_dest);
public:
	SendSelfOnClick();
	virtual ~SendSelfOnClick();

	virtual void onClick() override;
	virtual void onHoverStart() override;
	virtual void onHoverEnd() override;

	void pausedListener(kitten::Event::EventType p_type, kitten::Event* p_data);
	void setTileInfoDisplay(puppy::TextBox* p_info) { m_tileInfoDisplay = p_info; }
};
