#pragma once
#include "kitten\mouse picking\Clickable.h"

class DestroyOnClick : public kitten::Clickable
{
public:
	DestroyOnClick(nlohmann::json& p_json);
	DestroyOnClick();
	~DestroyOnClick();

	virtual void onClick() override;
};