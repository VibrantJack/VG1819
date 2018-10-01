#pragma once

#include <string>
#include "kitten\mouse picking\Clickable.h"

class PrintWhenClicked : public kitten::Clickable
{
private:
	std::string m_message;
public:
	PrintWhenClicked(const std::string& p_message);
	virtual ~PrintWhenClicked();

	virtual void setMessage(const std::string& p_message);

	virtual void onClick() override;

	// Not good programming to have onHover's in PrintWhenClicked,
	// but this is a debug component so I'm inclined to let this one slide
	// -Callum
	virtual void onHoverStart() override;
	virtual void onHoverEnd() override;
};