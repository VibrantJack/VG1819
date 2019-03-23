#pragma once
#include "kitten/K_Common.h"
#include "board/tile/TileInfo.h"
#include "json.hpp"
#include "kibble\json\jsonextra.hpp"

class GameModeComponent
{
public:
	enum TileType
	{
		SpawnPoint0 = -1,//spawn point for client 0
		Unknow = 0,//default
		SpawnPoint1 = 1,//spawn point for client 1
		ControlArea = 2,//king of hill mode
		DefendArea = 3,//attack / defend mode
		ItemSpawnArea = 4,//capture the flag mode
		ItemDropArea0 = 5,//capture the flag mode, for client 0
		ItemDropArea1 = 6,//capture the flag mode, for client 1
	};
public:
	GameModeComponent();
	~GameModeComponent();


	//add tile info that this class will focus on
	virtual void addTile(TileInfo* p_info);

	virtual void init();
	virtual void check() {};

	virtual void setProperty(nlohmann::json* p_jsonfile) {};

protected:
	//tiles for checking
	std::vector<TileInfo*> m_tileList;

	//tiles need to change to this texture to show it is this area
	std::string m_texturePath;

	virtual void changeTexture();

};