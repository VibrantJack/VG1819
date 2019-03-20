#pragma once
#include "kitten/K_Common.h"
#include "board/tile/TileInfo.h"

class GameModeComponent
{
public:
	enum TileType
	{
		Unknow = 0,//default
		SpawnPoint = 1,//normal
		ControlArea,//king of hill mode
		DefendArea,//attack / defend mode
		FlagSpawnArea,//capture the flag mode
		FlagDropArea,//capture the flag mode
	};
public:
	GameModeComponent();
	~GameModeComponent();


	//add tile info that this class will focus on
	virtual void addTile(TileInfo* p_info);

	virtual void check() {};

protected:
	std::vector<TileInfo*> m_tileList;

};