#pragma once
#include "../GameModeManager.h"

class ItemKeepArea : public GameModeComponent
{
public:
	ItemKeepArea(int p_id);
	~ItemKeepArea();

	virtual void check() override;
	virtual void setProperty(nlohmann::json* p_jsonfile) override;
private:
	const int m_clientId;

	//point gain for each item
	int m_pointPerItem;
};