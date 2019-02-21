#pragma once
#include <string>
#include "kitten\K_Component.h"


class DebugPrintOnce : public kitten::K_Component
{
private:
	std::string m_message;
public:
	DebugPrintOnce(nlohmann::json& p_json);
	DebugPrintOnce(const std::string p_message);
	virtual ~DebugPrintOnce();

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;
};