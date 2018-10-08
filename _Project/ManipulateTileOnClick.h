#pragma once

#include "kitten\mouse picking\Clickable.h"

class ManipulateTileOnClick : public kitten::Clickable
{
public:
	ManipulateTileOnClick();
	virtual ~ManipulateTileOnClick();

	virtual void onClick() override;
};