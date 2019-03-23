#pragma once
#include "../GameModeManager.h"

class ItemSpawnArea : public GameModeComponent
{
public:
	ItemSpawnArea();
	~ItemSpawnArea();

	virtual void check() override;
	virtual void setProperty(nlohmann::json* p_jsonfile) override;
private:
	//number of items to spawn each time
	int m_itemPerSpawn;

	//number of turns to wait for next spawn
	int m_turnWait;
	int m_turnPass;//number of turns that passed from last spawn

	//number of turns to wait for first spawn
	int m_delay;

	//item path
	std::string m_itemPath;
};
