#include "ability/ability/Ability.h"
#include "unit/Unit.h"
#include "board/tile/TileInfo.h"
#include "board/BoardManager.h"
//Rock

namespace ability
{
	int Oppose::effect(AbilityInfoPackage* p_info)
	{
		//get push back power
		int movepower = p_info->m_intValue[PUSH_BACK];

		//get source and target
		unit::Unit* source = p_info->m_source;
		unit::Unit* target = p_info->m_targets[0];

		if (target->canMove())
		{
			//get both position
			std::pair<int, int> pos1 = source->getTile()->getComponent<TileInfo>()->getPos();
			std::pair<int, int> pos2 = target->getTile()->getComponent<TileInfo>()->getPos();

			//get direction
			int dir = getDirection(pos1, pos2);

			//get tile for target to move
			kitten::K_GameObject* tile = getTile(target->getTile(), movepower, dir);

			//move target
			if (tile != target->getTile())
				target->move(tile);
		}

		if (source->getTile()->getComponent<TileInfo>()->isDemonicPresence())
		{
			//damage target and delete package
			singleTargetDamage(p_info);
		}
		else
		{
			done(p_info);
		}

		return 0;
	}

	kitten::K_GameObject * Oppose::getTile(kitten::K_GameObject* p_tile, int p_length, int p_direction)
	{
		BoardManager* bm = BoardManager::getInstance();

		kitten::K_GameObject* lastTile = p_tile;
		for (int i = 0; i < p_length; i++)
		{
			TileInfo* info = lastTile->getComponent<TileInfo>();
			int x = info->getPosX();
			int y = info->getPosY();

			kitten::K_GameObject* nextTile;
			switch (p_direction)
			{
			case 2:
				nextTile = bm->getTile(x, y + 1);
				break;
			case 4:
				nextTile = bm->getTile(x + 1, y);
				break;
			case 6:
				nextTile = bm->getTile(x - 1, y);
				break;
			case 8:
				nextTile = bm->getTile(x, y - 1);
				break;
			}

			if (nextTile != nullptr)
			{
				bool check = checkTile(nextTile, p_length);
				if (check)
					lastTile = nextTile;
				else
					break;
			}
			else
				break;
		}

		return lastTile;
	}

	int Oppose::getDirection(const std::pair<int, int>& p_pos1, const std::pair<int, int>& p_pos2)
	{
		//get direction
		//direction code
		//	 2
		//4		6
		//	 8
		if (p_pos1.first == p_pos2.second)//in y direction
		{
			if (p_pos1.second > p_pos2.second)//source push target down
				return 8;
			else if (p_pos1.second < p_pos2.second)//source push target up
				return 2;
		}
		else if (p_pos1.second == p_pos2.second)
		{
			if (p_pos1.first > p_pos2.first)//source push target right
				return 6;
			else if (p_pos1.first < p_pos1.first)//source push target left
				return 4;
		}

		assert(false);//didn't get direction
		return 0;
	}

	bool Oppose::checkTile(kitten::K_GameObject* p_tileGO, int p_movePower)
	{
		//get tile
		TileInfo* info = p_tileGO->getComponent<TileInfo>();

		//check is there unit on tile
		if (info->hasUnit())
			return false;

		//check if the tile can be passed
		if (info->getMVCost() > p_movePower)
			return false;

		return true;
	}

}