#pragma once

#include "kitten\K_Component.h"

class ResolutionController : public kitten::K_Component
{
private:
	virtual void start() override;
public:
	ResolutionController();
	~ResolutionController();
};