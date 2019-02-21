#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_Time.h"
#include "puppy\Text\TextBox.h"

class FPSCalc : public kitten::K_Component
{
private:
	kitten::K_Time* m_timeRef;
	int m_fps = 0;

	puppy::TextBox* m_textBox;
public:
	FPSCalc();
	FPSCalc(nlohmann::json& p_json);
	~FPSCalc();

	void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;
};