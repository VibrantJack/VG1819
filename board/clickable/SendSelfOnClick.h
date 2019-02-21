#pragma once

#include <string>
#include "kitten/mouse picking/Clickable.h"
#include "puppy\Text\TextBox.h"

class SendSelfOnClick : public kitten::Clickable
{
private:
	puppy::TextBox* m_tileInfoDisplay;

	void setTileInfoDisplayText();
	void getPadding(const std::string& p_string, std::string& p_dest);

	bool m_contextEnabled;
public:
	SendSelfOnClick();
	SendSelfOnClick(nlohmann::json& p_json);
	virtual ~SendSelfOnClick();

	virtual void onClick() override;
	virtual void onHoverStart() override;
	virtual void onHoverEnd() override;
	virtual void onPause() override;

	void setTileInfoDisplay(puppy::TextBox* p_info) { m_tileInfoDisplay = p_info; }
};
