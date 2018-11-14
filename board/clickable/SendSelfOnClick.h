#pragma once

#include <string>
#include "kitten/mouse picking/Clickable.h"

class SendSelfOnClick : public kitten::Clickable
{
public:
	SendSelfOnClick();
	virtual ~SendSelfOnClick();

	virtual void onClick() override;
	virtual void onHoverStart() override;
	virtual void onHoverEnd() override;
};
