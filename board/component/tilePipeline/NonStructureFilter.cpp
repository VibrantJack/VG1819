#include "TileFliter.h"

bool NonStructureFilter::shouldRemove(kitten::K_GameObject * p_tileGO)
{
	if (p_tileGO->getComponent<TileInfo>()->hasUnit())
	{
		kitten::K_GameObject* u = p_tileGO->getComponent<TileInfo>()->getUnit();
		unit::Unit* unit = u->getComponent<unit::Unit>();

		if (!unit->checkTag(STRUCTURE) && !unit->checkTag(MACHINE))
			return true;
	}
	return false;
}