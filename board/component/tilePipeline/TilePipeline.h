/*Rock 10.26

Remove tiles that meets some conditions from tile list.

*/

#pragma once
#include "board/component/tilePipeline/TileFliter.h"
#include <unordered_map>

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
	std::unordered_map<std::string, TileFilter*> *m_filterList;
};