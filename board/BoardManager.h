/*
 Rock 10.18
 
 This class manages all board related functions. 
 Include create board, get tile, highlight tile.
 */


#pragma once
#include "components/PowerTracker.h"
#include "board/component/BoardCreator.h"
#include "board/component/Range.h"
#include "board/component/Highlighter.h"
#include "board/tile/TileInfo.h"
#include "board/component/tilePipeline/TilePipeline.h"
#include "board/component/area/Area.h"
#include "board/component/PathFind.h"

class TilePipeline;
class BoardManager
{
public:
	static void createInstance() { assert(sm_instance == nullptr); sm_instance = new BoardManager(); };
	static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
	static BoardManager * getInstance() { return sm_instance; };

	//spawn point
	void setSpawnPoint(kitten::Event::TileList p_list);
	kitten::K_GameObject* getSpawnPoint(int m_clientId = -1);

	//dimension and tiles
	void setTileList(std::vector<kitten::K_GameObject*> p_list);
	void setDimension(int p_x, int p_z);
	std::pair<int, int> getDimension();
	kitten::K_GameObject* getTile(int p_x, int p_z);

	//power tracker
	void setPowerTracker(PowerTracker* p_pt) { m_powerTracker = p_pt; };
	PowerTracker* getPowerTracker() { return m_powerTracker; };

	//highlight area
	void showArea(kitten::K_GameObject* p_pivot);
	void hideArea();
	kitten::Event::TileList getArea();

	//change select
	bool m_selectRepeat;
	void select();
	void deselect();

	//highlight range
	kitten::Event::TileList getRange();

	void setGrid(bool p_enabled);
	bool isGridEnabled() const;

	void registerEvent();
	void deregisterEvent();

	void tileClicked(bool p_send);

	//at every game, all components should reset
	void resetComponents();

	//auto click, for AI or auto casting ability
	//it will act like the tile object is clicked without player interaction
	void autoClick(kitten::K_GameObject* p_tile);
private:
	static BoardManager* sm_instance;

	std::pair<int, int> m_dimension;
	kitten::Event::TileList m_spawnPointList;

	kitten::K_GameObject* m_hlGO;
	Range* m_range;
	Highlighter* m_highlighter;
	TilePipeline* m_pipeline;
	PowerTracker* m_powerTracker;
	Area* m_area;
	//PathFind* m_pathFind;

	kitten::Event::TileList m_areaList;
	kitten::Event::TileList m_rangeList;
	kitten::Event::TileList m_selectList;
	bool m_select;
	int m_targetNum;
	int m_selectNum;

	std::vector<kitten::K_GameObject*> m_tileList;

	bool m_isGridEnabled;

	BoardManager();
	~BoardManager();

	void listenEvent(kitten::Event::EventType p_type, kitten::Event* p_data);
	void highlightTile(kitten::Event* p_data);
	void highlightTileWithList(kitten::Event* p_data);
	//void unhighlightTile(kitten::Event* p_data);

	void setFilter(const std::string& p_filter, kitten::Event* p_data);
	void applyFilter(kitten::Event::TileList* p_list);

	void setArea(kitten::Event* p_data);
};
