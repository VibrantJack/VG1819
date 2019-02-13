#include "TileFliter.h"

bool StructureFilter::shouldRemove(kitten::K_GameObject * p_tileGO)
{
	if (p_tileGO->getComponent<TileInfo>()->hasUnit())
	{
		kitten::K_GameObject* u = p_tileGO->getComponent<TileInfo>()->getUnit();

		if (u->getComponent<unit::Unit>()->isStructure())
			return true;
	}
	return false;
}