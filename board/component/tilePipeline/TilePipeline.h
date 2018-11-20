/*Rock 10.26

Remove tiles that meets some conditions from tile list.

*/

#pragma once
#include "board/component/tilePipeline/TileFliter.h"
#include <unordered_map>

#define FILTER_NO_UNIT "no_unit"
#define FILTER_UNIT "unit"
#define FILTER_OWNED_TILE "owned_tile"
#define FILTER_NO_COMMANDER "no_commander"

#define FILTER "filter"
#define AREA_FILTER "area_filter"

class TileFilter;
class TilePipeline
{
public:
	TilePipeline();
	~TilePipeline();

	void filterList(kitten::Event::TileList* p_list);

	void useFilter(const std::string& p_filter);

	void resetFilter();
private:
	std::unordered_map<std::string, TileFilter*> m_filterList;
};