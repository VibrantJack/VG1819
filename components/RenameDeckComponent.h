#pragma once
#include "kitten/K_Component.h"
#include "kitten\InputManager.h"

class RenameDeckComponent : public input::StringListener, public kitten::K_Component
{
private:
public:
	RenameDeckComponent();
	~RenameDeckComponent();

	virtual void start() override;

	virtual void onStringFinished(const std::string& p_string) override;
	virtual void onStringChanged(const std::string& p_string) override;
};