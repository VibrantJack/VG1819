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
		ControlArea,//king of hill
		DefendArea,//attack / defend
		FlagSpawnArea,//capture the flag
		FlagDropArea,//capture the flag
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