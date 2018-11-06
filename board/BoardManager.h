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

class TilePipeline;
class BoardManager
{
public:
	static void createInstance() { assert(sm_instance == nullptr); sm_instance = new BoardManager(); };
	static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
	static BoardManager * getInstance() { return sm_instance; };

	void setTileList(std::vector<kitten::K_GameObject*>* p_list);
	void setDimension(int p_x, int p_z);
	std::pair<int, int> getDimension();
	kitten::K_GameObject* getTile(int p_x, int p_z);

	void setPowerTracker(PowerTracker* p_pt) { m_powerTracker = p_pt; };
	PowerTracker* getPowerTracker() { return m_powerTracker; };

	void showArea(kitten::K_GameObject* p_pivot);
	void hideArea();

	void registerEvent();
	void deregisterEvent();
private:
	static BoardManager* sm_instance;

	std::pair<int, int> m_dimension;
	//kitten::K_GameObject* m_boardGO;

	Range* m_range;
	Highlighter* m_highlighter;
	TilePipeline* m_pipeline;
	PowerTracker* m_powerTracker;
	Area* m_area;


	std::vector<kitten::K_GameObject*> m_tileList;

	BoardManager();
	~BoardManager();

	void listenEvent(kitten::Event::EventType p_type, kitten::Event* p_data);
	void highlightTile(kitten::Event* p_data);
	void unhighlightTile(kitten::Event* p_data);

	void setArea(kitten::Event* p_data);
};
