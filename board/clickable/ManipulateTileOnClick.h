#pragma once

#include "kitten\mouse picking\Clickable.h"

class ManipulateTileOnClick : public kitten::Clickable
{
public:
	ManipulateTileOnClick();
	ManipulateTileOnClick(nlohmann::json& p_json);
	virtual ~ManipulateTileOnClick();

	virtual void onClick() override;
};