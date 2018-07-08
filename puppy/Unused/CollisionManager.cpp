#include "CollisionManager.h"
#include <iostream>

namespace puppy
{
	/*
	Collision Manager
	*/

	//private static
	std::vector<Collidable*> CollisionManager::sm_toCheck;

	//public static
	void CollisionManager::addCollidable(Collidable* p_toAdd)
	{
		CollisionManager::sm_toCheck.push_back(p_toAdd);
	}

	//public static
	void CollisionManager::removeCollidable(Collidable* p_toRemove)
	{
		//Search for the object in the vector
		std::vector<Collidable*>::iterator pos =
			std::find(CollisionManager::sm_toCheck.begin(), CollisionManager::sm_toCheck.end(), p_toRemove);

		if (pos != CollisionManager::sm_toCheck.end()) //If there was a match
		{
			CollisionManager::sm_toCheck.erase(pos); //remove it
		}
	}

	//public static
	bool CollisionManager::checkCollision(const glm::vec3* p_pos)
	{
		std::vector<Collidable*>::iterator it;

		for (it = CollisionManager::sm_toCheck.begin(); it != CollisionManager::sm_toCheck.end(); ++it)
		{
			if ((*it)->collides(p_pos))
			{
				return true;
			}
		}

		return false;
	}


	//public static 
	void CollisionManager::removeAll()
	{
		CollisionManager::sm_toCheck.clear();
	}


	/*
		Collidable
	*/

	bool Collidable::collides(const glm::vec3* p_toCheck) const
	{
		glm::vec3 max = getMax();
		glm::vec3 min = getMin();
		
		if (((*p_toCheck)[0] >= min[0] && (*p_toCheck)[0] <= max[0]) &&
			((*p_toCheck)[1] >= min[1] && (*p_toCheck)[1] <= max[1]) &&
			((*p_toCheck)[2] >= min[2] && (*p_toCheck)[2] <= max[2]))
		{
			return true;
		}
		//else
		return false;
	}

	
}