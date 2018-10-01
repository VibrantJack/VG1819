#pragma once
#include "kitten\K_Component.h"

class BoardCreator : public kitten::K_Component
{
private:
public:
	BoardCreator();
	~BoardCreator();

	virtual void start() override;
};